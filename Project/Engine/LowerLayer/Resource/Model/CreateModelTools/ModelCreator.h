#pragma once
#include "ModelDescAssembler/ModelDescAssembler.h"
#include "../ModelContainer/ModelContainer.h"
#include "../ModelStructure/Model.h"
#include "../ModelContextCmds.h"

class ModelContext::ModelCreator
{
public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
		ModelContext::ModelContainer& modelContainer_
	);

	template<Model::Type modelType>
	std::vector<Model*> Create
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			modelType != Model::Type::kCount,
			"Model::Type::KCountを選択してんじゃない",
			"ModelCreator.h"
		);

		std::vector<Model*> modelPtrContainer;

		for (UINT i = 0;i < numCreate_;++i)
		{
			//モデルのディスクリプションの要素を組み立てる
			auto [perDrawIndices, materialsGPU, meshletSize] = modelDescAssembler->Assemble(modelFileName_, materials_);

			///一つのDescに詰める
			ModelDescription modelDesc
			(
				modelName_ + std::to_string(numCreate++),
				perDrawIndices,
				modelRenderStates_,
				meshletSize
			);

			///モデルクラスのインスタンス化
			std::unique_ptr<Model> model = std::make_unique<Model>(modelType, modelDesc, materialsGPU);

			modelPtrContainer.emplace_back(model.get());

			//実体はモデルコンテナが握る
			modelContainer.Add(ModelContainer::Local_AddLicence{}, std::move(model));
		}

		//レンダーステートキャッシュに登録
		renderStatesCache.insert
		(
			renderStatesCache.end(),
			std::make_move_iterator(modelRenderStates_.begin()),
			std::make_move_iterator(modelRenderStates_.end())
		);

		return modelPtrContainer;
	}


	//PSO生成時に必要
	ModelContextCmds::WatchAllModelsRenderStatePattern WatchAllRenderStatesCmd(ProviderKey key_)const;

private:

	//生成数。ネーミング用
	UINT numCreate{};
	//モデルディスク組み立て役
	std::unique_ptr<ModelContext::ModelDescAssembler> modelDescAssembler;
	//PSO生成時に生成された全モデルのレンダーステートパターンが必要
	std::vector<RenderState> renderStatesCache;



	//生成したユニークはこいつが管理する
	ModelContext::ModelContainer& modelContainer;
	
};

