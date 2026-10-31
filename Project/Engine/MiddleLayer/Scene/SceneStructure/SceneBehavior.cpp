#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "SceneOutput/SceneOutput.h"
#include "AllSceneInterfaceInclude.h"


//外部
#include "../../../LowerLayer/Resource/Camera/CameraStructure/CameraDesc/CameraDesc.h"
//エンジン備え付けのカメラ
#include "../../../LowerLayer/Resource/Camera/PresetCameras/PresetCameraIncludes.h"


using namespace ProjectConfig::Render;

namespace
{
	auto const fileName = "SceneBehavior.cpp";
}

SceneBehavior::SceneBehavior(InstancingLicense license_)
{
	output = std::make_unique<Output>();
}

SceneBehavior::~SceneBehavior() = default;

void SceneBehavior::Update()
{
	//このシーンで使うカメラのアップデート
	output->usingCamera = cameraSystems->CameraUpdate();

	//このシーンのモデルのトランスフォームのアップデートを呼ぶ
	modelSystems->UpdateModelTransform<Model::Type::kDynamic>();
	
	if (output->leftStaticModelBatchingCnt-- == (UINT)NumBuffer::kDoubleBuffer)
	{
		modelSystems->UpdateModelTransform<Model::Type::kStatic>();
	}
}


SceneBehavior::Output const& SceneBehavior::WatchSceneOutput()const 
{
	return *output; 
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
		fileName
	);

	ErrorMessageOutput::Assert::DetectError
	(
		modelSystems_,
		"モデルシステムがぬるです(エンジンのせい)",
		fileName
	);

	cameraSystems = cameraSystems_;
	modelSystems = modelSystems_;

	//ヌルチェック重複は偽りの注意のせい

	//シーン出力ようにモデルコンテナのアドレスを格納
	if(modelSystems) output->modelContainer = modelSystems->WatchModelContainer();

	//初期化用のインターフェースの作成
	if (cameraSystems && modelSystems)
	{
		std::get<std::unique_ptr<SceneInitInterface>>(interfaces) = 
			std::make_unique<SceneInitInterface>(cameraSystems, modelSystems);

		std::get<std::unique_ptr<SceneRuntimeInterface>>(interfaces) =
			std::make_unique<SceneRuntimeInterface>(cameraSystems);

	}
}


void SceneBehavior::CreatePresetCamera()
{
	//各シーンに1つは存在するデバッグカメラを作成
	auto* debugCamera = std::get<std::unique_ptr<SceneInitInterface>>(interfaces)->
		CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");
}


