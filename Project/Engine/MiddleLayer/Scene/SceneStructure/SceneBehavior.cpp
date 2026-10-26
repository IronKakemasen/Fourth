#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "../../../LowerLayer/Resource/Camera/CameraStructure/CameraDesc/CameraDesc.h"


//外部
//エンジン備え付けのカメラ
#include "../../../LowerLayer/Resource/Camera/PresetCameras/PresetCameraIncludes.h"

#include "../ScenePreset/RenderingTestScene/RenderingTestScene.h"

using namespace ProjectConfig::Render;

void SceneBehavior::Update()
{
	//このシーンで使うカメラのアップデート
	output.usingCamera = cameraSystems->CameraUpdate();


	static Vector3 a;
	a.data.x += 0.008f;
	a.data.y += 0.008f;
	a.data.z += 0.008f;


	for (int i = 0;i < 10;++i)
	{
		RenderingTestScene::p[i]->RefTransform(0).Rotate(a);
	}


	//このシーンのモデルのトランスフォームのアップデートを呼ぶ
	modelSystems->UpdateModelTransform<Model::Type::kDynamic>();
	
	if (output.leftStaticModelBatchingCnt-- == (UINT)NumBuffer::kDoubleBuffer)
	{
		modelSystems->UpdateModelTransform<Model::Type::kStatic>();
	}
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
	CameraContext::FrontlineSystems* cameraSystems_,
	ModelContext::FrontlineSystems* modelSystems_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraSystems_ ,
		"カメラシステムがぬるです(エンジンのせい)",
		"SceneBehavior.cpp"
	);

	ErrorMessageOutput::Assert::DetectError
	(
		modelSystems_,
		"モデルシステムがぬるです(エンジンのせい)",
		"SceneBehavior.cpp"
	);

	cameraSystems = cameraSystems_;
	modelSystems = modelSystems_;

	//シーン出力ようにモデルコンテナのアドレスを格納
	output.modelContainer = modelSystems->WatchModelContainer();
}


void SceneBehavior::CreatePresetCamera()
{
	//各シーンに1つは存在するデバッグカメラを作成
	auto* debugCamera = CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");
}


