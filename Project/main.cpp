#include "Engine/EngineInterface.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //新たなシーンを作成するときは、パワーシェルでジェーソンファイル作成＆レジストリー登録
#ifdef _DEBUG
    aFourth<RenderingTestScene> engineInterface({ "RenderingTestScene" });

#else

    aFourth<RenderingTestScene> engineInterface({ "RenderingTestScene" });

#endif // _DEBUG


    engineInterface.Run();

    return 0;
}
