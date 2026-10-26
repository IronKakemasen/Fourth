#pragma once
#include "../SceneContext.h"
#include "../SceneStructure/SceneBehavior.h"

//外部
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"

#include "../../../LowerLayer/Resource/Model/ModelContext.h"


//FrontlineSystems
class SceneContext::SceneCreator
{
public:
	SceneCreator() = default;

	//シーンを作成する
	template<typename SceneType>
	std::unique_ptr<SceneType> Create
	(
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_
	)
	{
		auto sceneUnique = std::make_unique<SceneType>(SceneBehavior::InstancingLicense{});
		
		//他コンテキストのシステムをセット
		sceneUnique->SetSystems
		(
			ReceiveCameraSystems(cameraContextDiplomat_),
			ReceiveModelSystems(modelContextDiplomat_)
		);

		//プリセットカメラを備え付ける
		sceneUnique->CreatePresetCamera();

		//仮想初期化関数を呼ぶ
		static_cast<SceneBehavior*>(sceneUnique.get())->Init();

		//モデルをスタティックとダイナミックに分ける
		sceneUnique->SeparateModels();

		return sceneUnique;
	}

private:

	//FrontlineSystemsを一つもらう
	CameraContext::FrontlineSystems* ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);
	//FrontlineSystemsを一つもらう
	ModelContext::FrontlineSystems* ReceiveModelSystems(ModelContextDiplomat& modelContextDiplomat_);


};

