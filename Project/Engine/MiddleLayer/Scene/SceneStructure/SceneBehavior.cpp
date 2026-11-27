#include "PreCompileHeader.h"
#include "SceneBehavior.h"
#include "SceneOutput/SceneOutput.h"
#include "AllSceneInterfaceInclude.h"
#include "SceneConfig/SceneConfig.h"

//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"
#include "../../../LowerLayer/Resource/Camera/CameraStructure/CameraDesc/CameraDesc.h"
//エンジン備え付けのカメラ
#include "../../../LowerLayer/Resource/Camera/PresetCameras/PresetCameraIncludes.h"

#include "../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"


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
	//ゲームオブジェクト、モデルのトランスフォームの更新フラグをリセットする
	objSystems->ResetObjTransformFrameFlag();

	modelSystems->ResetModelTransformFrameFlag<Model::MeshUpdateType::kDynamic>();

	//オブジェ配置シーンのように静的オブジェクトを常に更新したい場合があるので分岐
	if (!sceneConfig->alwaysUpdateStatic)
	{
		if (output->leftStaticBatchingCnt == (UINT)NumBuffer::kDoubleBuffer)
		{
			modelSystems->ResetModelTransformFrameFlag<Model::MeshUpdateType::kStatic>();
		}
	}
	else
	{
		modelSystems->ResetModelTransformFrameFlag<Model::MeshUpdateType::kStatic>();
	}

	//ゲームオブジェクトの更新、トランスフォームの更新
	objSystems->UpdateObjController
	(
		*std::get<std::unique_ptr<SceneRuntimeInterface>>(interfaces)
	);
	
	//このシーンのモデルのトランスフォームのアップデートを呼ぶ
	modelSystems->UpdateModelTransform<Model::MeshUpdateType::kDynamic>();
	
	if (!sceneConfig->alwaysUpdateStatic)
	{
		if (output->leftStaticBatchingCnt == (UINT)NumBuffer::kDoubleBuffer)
		{
			modelSystems->UpdateModelTransform<Model::MeshUpdateType::kStatic>();
		}
	}
	else
	{
		modelSystems->UpdateModelTransform<Model::MeshUpdateType::kStatic>();
	}

	//このシーンで使うカメラのアップデート
	output->usingCamera = cameraSystems->UpdateCamera();

	//Staticののこりバッチング回数を1減らす
	output->leftStaticBatchingCnt--;
}


SceneBehavior::Output const& SceneBehavior::WatchSceneOutput()const 
{
	return *output; 
}

void SceneBehavior::DeleteInitInterface()
{
	std::get<std::unique_ptr<SceneInitInterface>>(interfaces).reset();
	Logger::Log("Delete SceneInitInterface", fileName);
}

void SceneBehavior::SeparateModels()
{
	modelSystems->SeparateModels();
}

void SceneBehavior::InitAllGameObj(std::string const& sceneName_)
{
	objSystems->InitAllGameObj
	(
		sceneName_,
		std::make_tuple
		(
			std::get<std::unique_ptr<SceneInitInterface>>(interfaces).get(),
			std::get<std::unique_ptr<SceneRuntimeInterface>>(interfaces).get()
		)
	);

	DeleteInitInterface();
}

void SceneBehavior::SetSystems
(
	CameraContext::FrontlineSystems* cameraSystems_,
	ModelContext::FrontlineSystems* modelSystems_,
	GameObjectContext::FrontlineSystems* objFrontlineSystems_,
	MaterialContext::FrontlineSystems* materialSystems_
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

	ErrorMessageOutput::Assert::DetectError
	(
		objFrontlineSystems_,
		"オブジェシステムがぬるです(エンジンのせい)",
		fileName
	);

	ErrorMessageOutput::Assert::DetectError
	(
		materialSystems_,
		"マテリアルシステムがぬるです(エンジンのせい)",
		fileName
	);

	cameraSystems = cameraSystems_;
	modelSystems = modelSystems_;
	objSystems = objFrontlineSystems_;
	materialSystems = materialSystems_;

	//ヌルチェック重複は偽りの注意のせい

	//シーン出力ようにモデルコンテナのアドレスを格納
	if(modelSystems) output->modelContainer = modelSystems->WatchModelContainer();

	//初期化用のインターフェースの作成
	if (cameraSystems && modelSystems && objSystems && materialSystems)
	{
		std::get<std::unique_ptr<SceneInitInterface>>(interfaces) = 
			std::make_unique<SceneInitInterface>
			(
				*cameraSystems, 
				*modelSystems,
				*objSystems,
				*materialSystems
			);

		std::get<std::unique_ptr<SceneRuntimeInterface>>(interfaces) =
			std::make_unique<SceneRuntimeInterface>
			(
				*cameraSystems,
				*objSystems
			);

		//全描画対象のマテリアルバッチング用データのアドレスを渡す
		output->materialBatchFormatsPtr = &materialSystems->RefMaterialBatchFormatsArr();
	}
}

void SceneBehavior::SetSceneConfig(std::unique_ptr<SceneConfig>&& sceneConfig_)
{
	sceneConfig = std::move(sceneConfig_);

	output->alwaysUpdateStatic = sceneConfig->alwaysUpdateStatic;
}

void SceneBehavior::CreatePresetCamera()
{
	//各シーンに1つは存在するデバッグカメラを作成
	auto* debugCamera = std::get<std::unique_ptr<SceneInitInterface>>(interfaces)->
		CreateCamera<CameraSocket::kDebug, DefaultDebugCamera>(std::nullopt, "DefaultDebugCamera");
}


