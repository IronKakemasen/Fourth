#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/Device/DeviceContext.h"
#include "LowerLayer/Core/Device/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "LowerLayer/Core/Device/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/DescriptorHeap/DescriptorHeapContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/Window/WindowContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/SwapChain/SwapChainContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/Command/CommandContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Resource/Shader/ShaderContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Resource/Buffer/BufferContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Resource/PSO/PSO_Context.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Resource/RootSignature/RootSignatureContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Resource/Mesh/MeshContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Render/RenderContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace
{
	std::string const fileName = "Nexus.cpp";
}

using namespace ProjectConfig::Window;

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

//Nexusクラスのインスタンスを1つに制限する
bool Nexus::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

Nexus::Nexus()
{
	Logger::Entry("Nexus: Constructor");

	//自身のインスタンス制限
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), "Nexusクラスが複数具現化されてます", fileName);

	InstantiateInSequence<InitSequence::kDeviceContext>();
	InstantiateInSequence<InitSequence::kWindowContext>();
	InstantiateInSequence<InitSequence::kDescriptorHeapContext>();
	InstantiateInSequence<InitSequence::kBufferContext>();
	InstantiateInSequence<InitSequence::kCommandContext>();
	InstantiateInSequence<InitSequence::kSwapChainContext>();
	InstantiateInSequence<InitSequence::kShaderContext>();
	InstantiateInSequence<InitSequence::kPSO_Context>();
	InstantiateInSequence<InitSequence::kRootSignatureContext>();
	InstantiateInSequence<InitSequence::kMeshContext>();
	InstantiateInSequence<InitSequence::kRenderContext>();

	ErrorMessageOutput::Assert::DetectError(next == InitSequence::kEnd, "初期化が正常に行われていない可能性がある", fileName);
	Logger::End("Nexus: Constructor");
}

void Nexus::Finalize()
{
	commandContext->Finalize(CommandContext::InstanceKey{});
	windowContext->Finalize();
}

Nexus::~Nexus()
{
	Finalize();

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kDeviceContext>()
{
	//deviceContextクラスのインスタンス化
	deviceContext.reset(new DeviceContext(DeviceContext::InstanceKey{}));
	Logger::Log("Instantiate: deviceContext", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kWindowContext>()
{
	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::InstanceKey{}));
	Logger::Log("Instantiate: windowContext", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kDescriptorHeapContext>()
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

	std::array<UINT, 3> tmpSizeArray = { sizeArray.rtv ,sizeArray.srv,sizeArray.dsv };

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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kBufferContext>()
{
	auto* cmdProvider = deviceContext->commandProvider.get();

	//リソース生成コマンド
	auto createResourceCommand = cmdProvider->ProvideCreateResourceCommand();
	Logger::Log("Set: CommandCreateResource", fileName);

	bufferContext.reset(new BufferContext(BufferContext::InstanceKey{}, createResourceCommand, descriptorHeapContext.get()));
	Logger::Log("Instantiate: bufferContext", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kCommandContext>()
{
	auto* cmdExecutor = deviceContext->commandExecutor.get();

	//メイン
	auto [cmdQueue, cmdAllocators, cmdList] =
		cmdExecutor->CreateCommandContextCorePartsForRuntime(DeviceContext::InstanceKey{});

	//リソースアップロード用
	auto [allocator_forUpload, cmdList_forUpload] =
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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kSwapChainContext>()
{
	auto* cmdProvider = deviceContext->commandProvider.get();

	swapChainContext.reset
	(
		new SwapChainContext
		(
			SwapChainContext::InstanceKey{},
			descriptorHeapContext.get(),
			commandContext.get(),
			cmdProvider->ProvideCreateSwapChainCommand(),
			windowContext->WatchHWND()
		)
	);

	Logger::Log("Instantiate: swapChainContext", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kShaderContext>()
{
	shaderContext.reset(new ShaderContext(ShaderContext::InstanceKey{}));
	Logger::Log("Instantiate: ShaderContext", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kPSO_Context>()
{
	auto* cmdProvider = deviceContext->commandProvider.get();

	auto cmdCreateGraphicsPSO = cmdProvider->ProvideCreatePSOCommand<D3D12_PIPELINE_STATE_STREAM_DESC>();
	auto cmdCreateComputePSO = cmdProvider->ProvideCreatePSOCommand<D3D12_COMPUTE_PIPELINE_STATE_DESC>();

	pso_context.reset
	(
		new PSO_Context
		(
			PSO_Context::InstanceKey{},
			cmdCreateGraphicsPSO,
			cmdCreateComputePSO
		)
	);
	Logger::Log("Instantiate: PSO_Context", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kRootSignatureContext>()
{
	auto* cmdProvider = deviceContext->commandProvider.get();

	auto cmdCreateRootSignature = cmdProvider->ProvideCommandCreateRootSignature();

	rootSignatureContext.reset
	(
		new RootSignatureContext
		(
			RootSignatureContext::InstanceKey{},
			cmdCreateRootSignature
		)
	);

	Logger::Log("Instantiate: RootSignatureContext", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kRenderContext>()
{
	renderContext.reset(new RenderContext(RenderContext::InstanceKey{}));
	Logger::Log("Instantiate: RenderContext", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void Nexus::Instantiate<Nexus::InitSequence::kMeshContext>()
{
	meshContext.reset(new MeshContext(MeshContext::InstanceKey{}));
	Logger::Log("Instantiate: MeshContext", fileName);
}





template
void Nexus::Instantiate<Nexus::InitSequence::kDeviceContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kWindowContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kDescriptorHeapContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kBufferContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kCommandContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kSwapChainContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kShaderContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kPSO_Context>();

template
void Nexus::Instantiate<Nexus::InitSequence::kRootSignatureContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kMeshContext>();

template
void Nexus::Instantiate<Nexus::InitSequence::kRenderContext>();












