#include "PreCompileHedder.h"
#include "WinApp.h"
#include "WinAppInstanceLimiter.h"
#include "../Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "../Debug/ErrorMessageOutput/ErrorMessageOutput.h"

WinApp::WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_)
{
	//インスタンス制限
	std::string errorMessage = "WinAppクラスが複数具現化されてます";
	ErrorMessageOutput::OutputError(!InstanceLimiter::CanInstantiate(), errorMessage);

	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::AccessKey{}, width_, height_, windowName_));
}

WinApp::~WinApp()
{
	windowContext->Finalize(WindowContext::AccessKey{});
}