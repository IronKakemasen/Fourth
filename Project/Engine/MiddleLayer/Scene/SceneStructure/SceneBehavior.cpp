#include "PreCompileHeader.h"
#include "SceneBehavior.h"




SceneBehavior::SceneBehavior
(
	CameraContext::CameraFrontlineSystems* cameraSystems_
):cameraSystems(cameraSystems_)
{
	//各シーンに1つは存在するデバッグカメラを作成
	CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");


}

SceneBehavior::Output SceneBehavior::Update()
{
	Output output;

	//このシーンで使うカメラのアップデート
	output.usingCamera = cameraSystems->CameraUpdate();


	return output;
}


