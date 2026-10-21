#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "../../../LowerLayer/Resource/Camera/CameraStructure/CameraDesc/CameraDesc.h"


//外部
//エンジン備え付けのカメラ
#include "../../../LowerLayer/Resource/Camera/PresetCameras/PresetCameraIncludes.h"


void SceneBehavior::Update()
{
	//このシーンで使うカメラのアップデート
	output.usingCamera = cameraSystems->CameraUpdate();

}


SceneBehavior::Output const& SceneBehavior::WatchSceneOutput()const 
{
	return output; 
}

void SceneBehavior::SeparateModels()
{
	modelSystems->SeparateModels();
}

void SceneBehavior::SetSystems
(
	CameraContext::CameraFrontlineSystems* cameraSystems_,
	ModelContext::ModelFrontlineSystems* modelSystems_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraSystems_ && modelSystems_,
		"システムがぬるです",
		"SceneBehavior.cpp"
	);

	cameraSystems = cameraSystems_;
	modelSystems = modelSystems_;
}


void SceneBehavior::CreatePresetCamera()
{
	//各シーンに1つは存在するデバッグカメラを作成
	auto* debugCamera = CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");
}


