#pragma once
#include "../../CreateModelTools/ModelCreator.h"

class ModelContext::ModelFrontlineSystems
{
	//モデルのコンテナ。シーン1つにつき1こ。モデルの本体、renderState別と、
	//modelType別に分類されたコンテナも持つ
	class ModelContainer;

public:
	ModelFrontlineSystems(NexusFieldProof proof_, ModelCreator& modelCreator_);

	//モデル作成
	template<Model::Type modelType>
	std::vector<std::unique_ptr<Model>> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	)
	{
		AddModel
		(
			modelCreator.Create<modelType>
			(
				modelFileName_,
				modelRenderStates_,
				materials_,
				numCreate_,
				modelName_
			)
		);

	}

	//モデルコンテナの分別を行う
	void SeparateModels();

private:

	void AddModel(std::unique_ptr<Model>&& model_);

	std::unique_ptr<ModelContainer> modelContainer;
	ModelCreator& modelCreator;

};
