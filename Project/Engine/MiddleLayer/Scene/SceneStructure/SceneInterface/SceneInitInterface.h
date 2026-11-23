#pragma once


//外部
#include "../../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"

#include "../../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

#include "../../../GameObject/GameObjectRuntime/GameObjFrontSystems/GameObjFrontlineSystems.h"

#include "../../../../LowerLayer/Resource/Material/MaterialRuntime/MaterialFrontlineSystems/MaterialFrontlineSystems.h"

class SceneInitInterface
{
public:
	SceneInitInterface
	(
		CameraContext::FrontlineSystems& cameraSystems_,
		ModelContext::FrontlineSystems& modelSystems_,
		GameObjectContext::FrontlineSystems& objSystems_,
		MaterialContext::FrontlineSystems& materialSystems_
	):cameraSystems(cameraSystems_), modelSystems(modelSystems_),
		objSystems(objSystems_),materialSystems(materialSystems_)
	{

	}

	//カメラの作成＆登録
	template<CameraSocket dstSocket, typename CameraType>
	[[nodiscard]] CameraType* CreateCamera
	(
		std::optional<CameraDesc> const& cameraDesc_,
		std::string const& name_
	)
	{
		return cameraSystems.CreateCamera<dstSocket, CameraType>(cameraDesc_, name_);
	}

	//モデル作成し、そのポインタを返す
	template<Model::MeshUpdateType meshUpdateType,Materials::UpdateType materialUpdateType>
	[[nodiscard]] std::vector<Model*> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	)
	{
		//モデルを作成すると同時に、そのモデルのマテリアルのアドレスを更新タイプ別に回収する
		std::vector<Model*> models = modelSystems.CreateModel<meshUpdateType>
		(
			modelFileName_,
			modelRenderStates_,
			numCreate_,
			modelName_
		);

		for (auto* model : models)
		{
			auto materialsContainer = model->RefMaterialsContainer();
			for (auto& materials : materialsContainer)
			{
				materialSystems.CollectMaterialBatchFormat<materialUpdateType>(&materials);
			}
		}

		return models;
	}

	//ゲームオブジェクトにシステムをアタッチする
	template<typename SystemType>
	SystemType& AttachSystem(GameObjectBehavior& obj_)
	{
		return objSystems.AttachSystem<SystemType>(obj_);
	}

	//描画対象にマテリアルをアタッチする
	template<Material::Type type>
	auto& AttachMaterial(Materials& dst_)
	{
		return materialSystems.AttachMaterial<type>(dst_);
	}


private:

	CameraContext::FrontlineSystems& cameraSystems;
	ModelContext::FrontlineSystems& modelSystems;
	GameObjectContext::FrontlineSystems& objSystems;
	MaterialContext::FrontlineSystems& materialSystems;
};

