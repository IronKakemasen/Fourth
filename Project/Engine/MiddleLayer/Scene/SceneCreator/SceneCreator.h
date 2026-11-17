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

		//シーンのゲームオブジェクトの初期化、ランタイム用コンテナの構築
		scenePtr->InitAllGameObj(sceneName_);

		//モデルをスタティックとダイナミックに分ける
		sceneUnique->SeparateModels();

		return sceneUnique;
	}

private:

	//シーンのシステム群を他コンテキストから構成する
	template<typename SystemsType, typename DiplomatType>
	SystemsType* ReceiveSystems(DiplomatType& diplomat_);
};

template<>
CameraContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(CameraContextDiplomat& diplomat_);
template<>
ModelContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(ModelContextDiplomat& diplomat_);
template<>
GameObjectContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(GameObjectContextDiplomat& diplomat_);
template<>
MaterialContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(MaterialContextDiplomat& diplomat_);
