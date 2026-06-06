#include "PreCompileHedder.h"
#include "WinApp.h"
#include "../Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "../Debug/ErrorMessageOutput/ErrorMessageOutput.h"

WinApp::WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_)
{

	//自身のインスタンス制限
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), "WinAppクラスが複数具現化されてます", "WinApp.cpp");

	//メンバー変数のインスタンス化
	InstantiateMemberVariables(width_, height_, windowName_);
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

void WinApp::InstantiateMemberVariables(uint32_t width_, uint32_t height_, LPCWSTR windowName_)
{
	//deviceContextクラスのインスタンス化
	deviceContext.reset(new DeviceContext(DeviceContext::InstanceKey{}));

	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::CraftKey{}, width_, height_, windowName_));

	//gpuBufferCreatorクラスのインスタンス化
	gpuBufferCreator.reset(new GPUBufferCreator(GPUBufferCreator::InstanceKey{}));

}

void WinApp::GivingAndReceivingCommands()
{
	auto createConstantBufferCommand = deviceContext->GetBufferCreateCommand<ConstantBufferDescription>();
	auto createColorbufferCommand = deviceContext->GetBufferCreateCommand<ColorBufferDescription>();

	gpuBufferCreator->SetCommands(createColorbufferCommand, createConstantBufferCommand);
}