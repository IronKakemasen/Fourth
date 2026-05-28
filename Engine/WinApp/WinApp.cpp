#include "PreCompileHedder.h"
#include "WinApp.h"
#include "WinAppInstanceLimiter.h"

WinApp::WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_)
{
	//インスタンス制限
	if (!WinApp::InstanceLimiter::CanInstantiate()) assert(false && "WinAppクラスが複数具現化されてます");

	//windowContextのインスタンス化
	windowContext.reset(new WindowContext(WindowContext::AccessKey{}, width_, height_, windowName_));
}

WinApp::~WinApp()
{
	windowContext->Finalize();
}