#include "Lowerlayer/Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "Nexus/Nexus.h"

void Update(Nexus& nexus_);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // デバッガー。DebugLayer, PointerValidator, LeakChecker
    RuntimeDebugger runtimeDebugger;
    // エンジンの交易場
    Nexus nexus;

    Update(nexus);

    return 0;
}

void Update(Nexus& nexus_)
{
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
            nexus_.Run();
        }
    }
}

