#include "Engine/EngineInterface.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //新たなシーンを作成するときは、パワーシェルでジェーソンファイル作成＆レジストリー登録
    aFourth<RenderingTestScene> engineInterface({ "RenderingTestScene" });

    engineInterface.Run();

    return 0;
}
