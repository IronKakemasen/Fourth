#include "PreCompileHeader.h"
#include "RenderingTestScene.h"
#include "../../../GameObject/GameObjectPreset/GridFloor/GridFloor.h"

void RenderingTestScene::Init()
{
	CreateObj<GridFloor>("Test");

}



