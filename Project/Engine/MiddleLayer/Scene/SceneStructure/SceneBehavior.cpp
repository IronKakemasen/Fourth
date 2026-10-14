#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "../../../LowerLayer/Resource/Camera/CameraStructrue/CameraDesc/CameraDesc.h"




SceneBehavior::SceneBehavior
(
	CameraContext::CameraFrontlineSystems& cameraSystems_
):cameraSystems(cameraSystems_)
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
