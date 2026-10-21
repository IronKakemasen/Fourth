#pragma once
#include "../../CreateModelTools/ModelCreator.h"

struct RenderStateKey;


class ModelContext::ModelFrontlineSystems
{
public:

	//モデルのコンテナ。シーン1つにつき1こ。モデルの本体、renderState別と、
	//modelType別に分類されたコンテナも持つ
	class ModelContainer;

	ModelFrontlineSystems(NexusFieldProof proof_, ModelCreator& modelCreator_);
	~ModelFrontlineSystems();

	//モデル作成し、そのポインタを返す
	template<Model::Type modelType>
	std::vector<Model*> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_
	)
	{
		return AddModel
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

	ModelContainer const* WatchModelContaienr()const;



private:

	std::vector<Model*> AddModel(std::vector<std::unique_ptr<Model>>&& modelUniques_);

	std::unique_ptr<ModelContainer> modelContainer;
	ModelCreator& modelCreator;

};
