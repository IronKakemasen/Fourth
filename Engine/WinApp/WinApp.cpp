#include "PreCompileHedder.h"
#include "WinApp.h"
#include "../Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "../Debug/ErrorMessageOutput/ErrorMessageOutput.h"
#include "../Core/Device/DeviceContextCommandProvider/DeviceContextCommandProvider.h"

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

	//メンバー変数のインスタンス化
	InstantiateMemberVariables();
	Logger::Log("Instantiate : CoreSystems ", fileName);

	//コマンドの授受
	GivingAndReceivingCommands();
	Logger::Log("Complete: Giving Commands ", fileName);

	//DescriptorHeapの生成
	CreateDescriptorHeaps();
	Logger::Log("Create: DescriptorHeaps", fileName);


	Logger::End("WinApp: Constructor");
}

WinApp::~WinApp()
{
	windowContext->Finalize();
}

//WinAppクラスのインスタンスを1つに制限する
bool WinApp::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

void WinApp::InstantiateMemberVariables()
{
	//deviceContextクラスのインスタンス化
	deviceContext.reset(new DeviceContext(DeviceContext::InstanceKey{}));
	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::CraftKey{}));
	//gpuBufferCreatorクラスのインスタンス化
	gpuBufferCreator.reset(new GPUBufferCreator(GPUBufferCreator::InstanceKey{}));
	//descriptorHeapContextクラスのインスタンス化
	descriptorHeapContext.reset(new DescriptorHeapContext(DescriptorHeapContext::InstanceKey{}));

}

void WinApp::GivingAndReceivingCommands()
{
	//バッファ生成コマンド
	{
		const auto& createConstantBufferCommand = deviceContext->commandProvider->PassCreateBufferCommand<ConstantBufferDescription>();
		const auto& createColorbufferCommand = deviceContext->commandProvider->PassCreateBufferCommand<ColorBufferDescription>();

		gpuBufferCreator->SetCommands(createColorbufferCommand, createConstantBufferCommand);
	}

	//DescriptorHeap生成コマンド
	{
		auto createDescriptorHeapCommand = deviceContext->commandProvider->PassCreateDescriptorHeapCommand();

		descriptorHeapContext->SetCommand(createDescriptorHeapCommand);
	}

}

void WinApp::CreateDescriptorHeaps()
{
	using namespace ProjectConfig::Core;

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
		deviceContext->PassDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV),
		deviceContext->PassDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV),
		deviceContext->PassDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV)
	);

	//RTV
	descriptorHeapContext->CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(kNumDescriptorsRTVHeap, false, sizeArray.rtv);
	//SRV
	descriptorHeapContext->CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(kNumDescriptorSRVHeap, false, sizeArray.srv);
	//DSV
	descriptorHeapContext->CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(kNumDescriptorsDSVHeap, false, sizeArray.dsv);
}

