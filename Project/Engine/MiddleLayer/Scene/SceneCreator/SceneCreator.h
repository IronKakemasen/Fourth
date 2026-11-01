#pragma once
#include "../SceneContext.h"
#include "../SceneStructure/SceneBehavior.h"


//FrontlineSystems
class SceneContext::SceneCreator
{
public:
	SceneCreator() = default;

	//シーンを作成する
	template<typename SceneType>
	std::unique_ptr<SceneType> Create
	(
		std::string const& sceneName_,
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		GameObjectContextDiplomat& gameObjectContextDiplomat_
	)
	{
		auto sceneUnique = std::make_unique<SceneType>(SceneBehavior::InstancingLicense{});
		
		//他コンテキストのシステムをセット
		sceneUnique->SetSystems
		(
			ReceiveCameraSystems(cameraContextDiplomat_),
			ReceiveModelSystems(modelContextDiplomat_),
			ReceiveObjSystems(gameObjectContextDiplomat_)
		);

		//プリセットカメラを備え付ける
		sceneUnique->CreatePresetCamera();

		auto* scenePtr = static_cast<SceneBehavior*>(sceneUnique.get());

		//仮想初期化関数を呼ぶ
		scenePtr->Init();

		//シーンのゲームオブジェクトの初期化、ランタイム用コンテナの構築
		scenePtr->InitAllGameObj(sceneName_);

		//モデルをスタティックとダイナミックに分ける
		sceneUnique->SeparateModels();

		return sceneUnique;
	}

private:

	CameraContext::FrontlineSystems* ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);
	ModelContext::FrontlineSystems* ReceiveModelSystems(ModelContextDiplomat& modelContextDiplomat_);
	GameObjectContext::FrontlineSystems* ReceiveObjSystems(GameObjectContextDiplomat& gameObjectContextDiplomat_);

};

