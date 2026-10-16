#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "../../../LowerLayer/Resource/Camera/CameraStructrue/CameraDesc/CameraDesc.h"


//外部
//エンジン備え付けのカメラ
#include "../../../LowerLayer/Resource/Camera/PresetCameras/PresetCameraIncludes.h"



SceneBehavior::SceneBehavior
(
	CameraContext::CameraFrontlineSystems& cameraSystems_,
	ModelContext::ModelFrontlineSystems& modelSystems_
):cameraSystems(cameraSystems_), modelSystems(modelSystems_)
{
	//各シーンに1つは存在するデバッグカメラを作成
	CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");


}

void SceneBehavior::Update()
{
	//このシーンで使うカメラのアップデート
	output.usingCamera = cameraSystems.CameraUpdate();

}


SceneBehavior::Output const& SceneBehavior::WatchSceneOutput()const 
{
	return output; 
}
