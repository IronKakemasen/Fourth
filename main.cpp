#include "Engine/Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "Engine/WinApp/WinApp.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // デバッガー。DebugLayer, PointerValidator, LeakChecker
    RuntimeDebugger runtimeDebugger;
    // アプリケーションクラス
    WinApp winApp;

    MSG msg = {};

    while (true)
    {
        //Windowにメッセージが来てたら最優先で処理させる
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {

        }
    }

    return 0;
}