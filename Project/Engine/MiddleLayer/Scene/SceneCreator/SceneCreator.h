#pragma once
#include "../SceneContext.h"
#include "../SceneStructure/SceneConfig/SceneConfig.h"


//FrontlineSystems
class SceneContext::SceneCreator
{
	//jsonにあるシーンのコンフィグを読み込む
	class SceneConfigLoder;

public:
	SceneCreator() = default;

	//シーンを作成する
	template<typename SceneType>
	std::unique_ptr<SceneType> Create
	(
		std::string const& sceneName_,
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		GameObjectContextDiplomat& gameObjectContextDiplomat_,
		MaterialContextDiplomat& materialContextDiplomat_
	)
	{
		auto sceneUnique = std::make_unique<SceneType>(SceneBehavior::InstancingLicense{});
		
		//他コンテキストのシステムをセット
		sceneUnique->SetSystems
		(
			ReceiveSystems<CameraContext::FrontlineSystems>(cameraContextDiplomat_),
			ReceiveSystems<ModelContext::FrontlineSystems>(modelContextDiplomat_),
			ReceiveSystems<GameObjectContext::FrontlineSystems>(gameObjectContextDiplomat_),
			ReceiveSystems<MaterialContext::FrontlineSystems>(materialContextDiplomat_)
		);

		//プリセットカメラを備え付ける
		sceneUnique->CreatePresetCamera();

		auto* scenePtr = static_cast<SceneBehavior*>(sceneUnique.get());

		//仮想初期化関数を呼ぶ
		scenePtr->Init();

		//シーン設定をジェーソンファイルから読み込む
		scenePtr->SetSceneConfig(LoadSceneConfig(sceneName_));

		//シーンのゲームオブジェクトの初期化、ランタイム用コンテナの構築
		scenePtr->InitAllGameObj(sceneName_);

		//モデルをスタティックとダイナミックに分ける
		scenePtr->SeparateModels();

		return sceneUnique;
	}

private:

	//シーンのシステム群を他コンテキストから構成する
	template<typename SystemsType, typename DiplomatType>
	SystemsType* ReceiveSystems(DiplomatType& diplomat_);

	//シーン設定をジェーソンファイルから読み込む
	std::unique_ptr<SceneBehavior::SceneConfig> LoadSceneConfig(std::string const& sceneName_);
};

template<>
CameraContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(CameraContextDiplomat& diplomat_);
template<>
ModelContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(ModelContextDiplomat& diplomat_);
template<>
GameObjectContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(GameObjectContextDiplomat& diplomat_);
template<>
MaterialContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(MaterialContextDiplomat& diplomat_);
