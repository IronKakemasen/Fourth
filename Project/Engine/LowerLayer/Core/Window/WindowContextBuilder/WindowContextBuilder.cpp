#include "PreCompileHeader.h"
#include "WindowContextBuilder.h"
#include "DumpExporter.h"
#include "../WindowProcedure/WindowProcedure.h"

//外部
#include "StringConverter/StringConverter.h"

namespace
{
	auto const fileName = "WindowContextBuilder.cpp";
}

WindowContext::CoreParts WindowContext::Builder::CreateCoreParts()
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
	wc.lpfnWndProc = WindowContext::WindowProcedure::WndProc;
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


WindowContext::CoreParts WindowContext::Builder::Build(NexusFieldProof proof_)
{
	auto coreParts = CreateCoreParts();
	Logger::Log("Create: CoreParts", fileName);
	Logger::Log(StringConverter::ConvertString(coreParts.windowName) + " " + std::to_string(coreParts.width) + "x" + std::to_string(coreParts.height), fileName);


	//ウィンドウの表示
	ShowWindow(coreParts.hWnd, SW_SHOWNORMAL);
	Logger::Log("Display Window", fileName);

	//ウィンドウにフォーカス
	SetFocus(coreParts.hWnd);
	Logger::Log("Focus on Window", fileName);

	//誰も捕捉しなかった場合に(Unhandled)、補足する関数を登録
	SetUnhandledExceptionFilter(ExportDump);
	Logger::Log("Set Unhandled Exception Filter", fileName);

	return coreParts;
}