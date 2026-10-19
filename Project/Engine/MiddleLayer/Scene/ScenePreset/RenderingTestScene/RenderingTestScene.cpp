#include "PreCompileHeader.h"
#include "RenderingTestScene.h"


RenderingTestScene::RenderingTestScene
(
	CameraContext::CameraFrontlineSystems& cameraSystems_,
	ModelContext::ModelFrontlineSystems& modelSystems_
): SceneBehavior(cameraSystems_, modelSystems_)
{

}
