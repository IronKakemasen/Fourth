#include "PreCompileHeader.h"
#include "Nexus.h"
#include "../Core/Device/DeviceContext.h"
#include "../Core/Window/WindowContext.h"
#include "../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../Resource/BufferContext.h"
#include "../Core/Device/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../Core/Device/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
#include "../Core/SwapChain/SwapChainContext.h"
#include "../Core/Command/CommandContext.h"
#include "../Resource/BufferAssembler/BufferAssembler.h"
#include "../Resource/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"
#include "../Resource/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"

namespace
{
	std::string const fileName = "Nexus.cpp";
}

//Nexusクラスのインスタンスを制御するクラス
class Nexus::InstanceLimiter
{
public:
	static bool CanInstantiate();

	InstanceLimiter(const InstanceLimiter&) = delete;
	InstanceLimiter& operator=(const InstanceLimiter&) = delete;
	InstanceLimiter(InstanceLimiter&&) = delete;
	InstanceLimiter& operator=(InstanceLimiter&&) = delete;

private:
	int instanceCnt{};

	~InstanceLimiter() = default;
	InstanceLimiter() = default;
};

Nexus::Nexus()
{
	Logger::Entry("Nexus: Constructor");

	//自身のインスタンス制限
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), "Nexusクラスが複数具現化されてます", fileName);

	InitDeviceContext();
	InitWindowContext();
	InitDescriptorHeapContext();
	InitBufferContext();
	InitCommandContext();
	InitSwapChainContext();

	Logger::End("Nexus: Constructor");
}

Nexus::~Nexus()
{
	windowContext->Finalize();
}

void Nexus::InitSwapChainContext()
{
	using namespace ProjectConfig::Window;
	BufferDescriptionBehavior::ResourceStates resourceStates = { D3D12_RESOURCE_STATE_DEPTH_WRITE ,D3D12_RESOURCE_STATE_DEPTH_WRITE };
	
	std::unique_ptr<DepthStencilBuffer> depthStencilBuffer;
	auto* cmdProvider = deviceContext->commandProvider.get();

	//スワップチェーンが使用する深度ステンシルバッファをここでつくちゃう
	{
		DepthStencilBufferDescription desc
		(
			kWidth,
			kHeight,
			0.0f,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			resourceStates
		);

		depthStencilBuffer = std::move(bufferContext->bufferAssembler->Assemble<DepthStencilBuffer>(desc, "SwapChain_DB"));
		Logger::Log("Create: SwapChainDepthStencilBuffer", fileName);
	}

	swapChainContext.reset
	(
		new SwapChainContext
		(
			SwapChainContext::InstanceKey{},
			descriptorHeapContext.get(),
			commandContext.get(),
			cmdProvider->ProvideCreateSwapChainCommand(),
			windowContext->WatchHWND(),
			std::move(depthStencilBuffer)
		)
	);

	Logger::Log("Instantiate: swapChainContext", fileName);
}

//Nexusクラスのインスタンスを1つに制限する
bool Nexus::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

void Nexus::InitDeviceContext()
{
	//deviceContextクラスのインスタンス化
	deviceContext.reset(new DeviceContext(DeviceContext::InstanceKey{}));
	Logger::Log("Instantiate: deviceContext", fileName);
}

void Nexus::InitBufferContext()
{
	auto* cmdProvider = deviceContext->commandProvider.get();

	//リソース生成コマンド
	auto createResourceCommand = cmdProvider->ProvideCreateResourceCommand();
	Logger::Log("Set: CommandCreateResource", fileName);

	bufferContext.reset(new BufferContext(BufferContext::InstanceKey{}, createResourceCommand,descriptorHeapContext.get()));
	Logger::Log("Instantiate: bufferContext", fileName);
}

void Nexus::InitWindowContext()
{
	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::InstacnceKey{}));
	Logger::Log("Instantiate: windowContext", fileName);

}

void Nexus::InitDescriptorHeapContext()
{
	auto* cmdProvider = deviceContext->commandProvider.get();
	auto* cmdExecutor = deviceContext->commandExecutor.get();

	//DescriptorHeap生成コマンド
	auto createDescriptorHeapCommand = cmdProvider->ProvideCreateDescriptorHeapCommand();
	auto createRTVCommand = cmdProvider->ProvideCreateViewCommand<D3D12_RENDER_TARGET_VIEW_DESC>();
	auto createSRVCommand = cmdProvider->ProvideCreateViewCommand<D3D12_SHADER_RESOURCE_VIEW_DESC>();
	auto createDSVCommand = cmdProvider->ProvideCreateViewCommand<D3D12_DEPTH_STENCIL_VIEW_DESC>();
	auto createUAVCommand = cmdProvider->ProvideCreateUAVCommand();

	struct IncrementSizeOfDescriptorHeaps
	{
		UINT rtv{};
		UINT srv{};
		UINT dsv{};
		IncrementSizeOfDescriptorHeaps(UINT rtv_, UINT srv_, UINT dsv_) : rtv(rtv_), srv(srv_), dsv(dsv_) {}
	};

	//deviceContextからDescriptorHandleIncrementSizeを教えてもらう
	IncrementSizeOfDescriptorHeaps sizeArray
	(
		cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV),
		cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV),
		cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV)
	);

	std::array<UINT,3> tmpSizeArray = { sizeArray.rtv ,sizeArray.srv,sizeArray.dsv };

	//descriptorHeapContextクラスのインスタンス化
	descriptorHeapContext.reset(new DescriptorHeapContext
	(
		DescriptorHeapContext::InstanceKey{},
		createDescriptorHeapCommand,
		createRTVCommand,
		createSRVCommand,
		createDSVCommand,
		createUAVCommand,
		tmpSizeArray
	));

	Logger::Log("Instantiate: descriptorHeapContext", fileName);
}

void Nexus::InitCommandContext()
{
	auto* cmdExecutor = deviceContext->commandExecutor.get();

	//メイン
	auto [cmdQueue, cmdAllocators, cmdList] = 
		cmdExecutor->CreateCommandContextCorePartsForRuntime(DeviceContext::InstanceKey{});
	
	//リソースアップロード用
	auto[allocator_forUpload, cmdList_forUpload] = 
		cmdExecutor->CreateCommandContextCorePartsForUpload(DeviceContext::InstanceKey{});

	commandContext.reset
	(
		new CommandContext
		(
			CommandContext::InstanceKey{},
			std::move(cmdQueue),
			std::move(cmdAllocators),
			std::move(cmdList),
			std::move(cmdExecutor->CreateFence()),
			std::move(allocator_forUpload),
			std::move(cmdList_forUpload)
		)
	);

	Logger::Log("Instantiate: commandContext", fileName);
}

void Nexus::Run()
{

}