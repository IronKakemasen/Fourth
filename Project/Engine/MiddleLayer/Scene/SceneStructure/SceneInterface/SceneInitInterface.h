#pragma once
#include "../SceneBehavior.h"

class SceneInitInterface
{
public:
	SceneInitInterface
	(
		CameraContext::FrontlineSystems* cameraSystems_,
		ModelContext::FrontlineSystems* modelSystems_
	):cameraSystems(cameraSystems_), modelSystems(modelSystems_)
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
		return cameraSystems->CreateCamera<dstSocket, CameraType>(cameraDesc_, name_);
	}

	//モデル作成し、そのポインタを返す
	template<Model::Type modelType>
	[[nodiscard]] std::vector<Model*> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	)
	{
		return modelSystems->CreateModel<modelType>
		(
			modelFileName_,
			modelRenderStates_,
			materials_,
			numCreate_,
			modelName_
		);
	}



private:

	CameraContext::FrontlineSystems* cameraSystems;
	ModelContext::FrontlineSystems* modelSystems;
};

