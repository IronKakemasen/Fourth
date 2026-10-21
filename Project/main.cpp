#include "Engine/EngineInterface.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    aFourth<RenderingTestScene> engineInterface({ "RenderingTestScene" });

    engineInterface.Run();

    return 0;
}
