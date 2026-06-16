#include "PreCompileHeader.h"
#include "WinApp.h"
#include "../Core/Device/DeviceContext.h"
#include "../Core/Window/WindowContext.h"
#include "../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../Resource/BufferContext.h"
#include "../Core/Device/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../Core/SwapChain/SwapChainContext.h"

namespace
{
	std::string const fileName = "WinApp.cpp";
}

//WinAppクラスのインスタンスを制御するクラス
class WinApp::InstanceLimiter
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

WinApp::WinApp()
{
	Logger::Entry("WinApp: Constructor");

	//自身のインスタンス制限
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), "WinAppクラスが複数具現化されてます", fileName);

	InitDeviceContext();
	InitWindowContext();
	InitDescriptorHeapContext();
	InitBufferContext();

	Logger::End("WinApp: Constructor");
}

WinApp::~WinApp()
{
	windowContext->Finalize();
}

void WinApp::InitSwapChainContext()
{
	//swapChainContext.reset(new SwapChainContext())
}

//WinAppクラスのインスタンスを1つに制限する
bool WinApp::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

void WinApp::InitDeviceContext()
{
	//deviceContextクラスのインスタンス化
	deviceContext.reset(new DeviceContext(DeviceContext::InstanceKey{}));
	Logger::Log("Instantiate: deviceContext", fileName);
}

void WinApp::InitBufferContext()
{
	//リソース生成コマンド
	auto createResourceCommand = deviceContext->commandProvider->ProvideCreateResourceCommand();
	Logger::Log("Set: CommandCreateResource", fileName);

	bufferContext.reset(new BufferContext(BufferContext::InstanceKey{}, createResourceCommand,descriptorHeapContext.get()));
	Logger::Log("Instantiate: bufferContext", fileName);
}

void WinApp::InitWindowContext()
{
	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::CraftKey{}));
	Logger::Log("Instantiate: windowContext", fileName);

}

void WinApp::InitDescriptorHeapContext()
{
	//DescriptorHeap生成コマンド
	auto createDescriptorHeapCommand = deviceContext->commandProvider->ProvideCreateDescriptorHeapCommand();
	auto createRTVCommand = deviceContext->commandProvider->ProvideCreateViewCommand<D3D12_RENDER_TARGET_VIEW_DESC>();
	auto createSRVCommand = deviceContext->commandProvider->ProvideCreateViewCommand<D3D12_SHADER_RESOURCE_VIEW_DESC>();
	auto createDSVCommand = deviceContext->commandProvider->ProvideCreateViewCommand<D3D12_DEPTH_STENCIL_VIEW_DESC>();
	auto createUAVCommand = deviceContext->commandProvider->ProvideCreateUAVCommand();

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
		deviceContext->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV),
		deviceContext->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV),
		deviceContext->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV)
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

