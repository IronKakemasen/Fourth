#include "PreCompileHeader.h"
#include "WindowContextBuilder.h"

namespace
{
	auto const fileName = "WindowContextBuilder.cpp";
}


WindowContext::CoreParts WindowContext::Builder::Build(NexusFieldProof proof_)
{
	CoreParts coreParts;

	using namespace ProjectConfig::Window;

	auto hInst = GetModuleHandle(nullptr);
	ErrorMessageOutput::Abort::DetectError(hInst, "hInstがぬるぽ", fileName);

	//ウィンドウクラスの登録
	WNDCLASSEX wc = {};

	coreParts.windowName = kTitle;
	coreParts.width = kWidth;
	coreParts.height = kHeight;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowContext::WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = kTitle;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	//ウィンドウの登録
	ErrorMessageOutput::Abort::DetectError(RegisterClassEx(&wc), "ウィンドウの登録失敗", fileName);

	//インスタンスハンドルの設定
	coreParts.hInst = hInst;

	//WindowSize
	RECT rc = {};
	rc.right = static_cast<LONG>(coreParts.width);
	rc.bottom = static_cast<LONG>(coreParts.height);
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウの作成
	coreParts.hWnd = CreateWindowEx
	(
		0,                              
		kTitle,               
		kTitle,					
		style,					
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,				
		nullptr,				
		coreParts.hInst,		
		nullptr					
	);

	ErrorMessageOutput::Abort::DetectError((coreParts.hWnd != NULL), "m_hWndがぬるぽ", fileName);


	return coreParts;
}