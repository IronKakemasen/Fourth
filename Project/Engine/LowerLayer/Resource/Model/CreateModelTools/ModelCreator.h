#pragma once
#include "../ModelContext.h"
#include "../ModelStructure/Model.h"

class ModelContext::ModelCreator
{
	class ModelDescAssembler;

	using ModelDescParts = std::tuple
	<
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU>,
		std::vector<StructuredBufferModelData::MaterialGPU>,
		std::vector<size_t>
	>;

public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		ModelSlotAllocator& slotAllocator_,
		TextureContextDiplomat& textureContextDiplomat_
	);

	~ModelCreator();

	template<Model::Type modelType>
	std::vector<std::unique_ptr<Model>> Create
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ 
	)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			modelType != Model::Type::kCount,
			"Model::Type::KCountを選択してんじゃない",
			"ModelCreator.h"
		);

		std::vector<std::unique_ptr<Model>> modelUniques;

		for (UINT i = 0;i < numCreate_;++i)
		{
			//モデルのディスクリプションの要素を組み立てる
			auto [perDrawIndices, materialsGPU, meshletSize] = AssembleModelDescParts(modelFileName_, materials_);

			///一つのDescに詰める
			ModelDescription modelDesc
			(
				modelName_ + std::to_string(numCreate++),
				perDrawIndices,
				modelRenderStates_,
				meshletSize
			);

			///モデルクラスのインスタンス化
			modelUniques.emplace_back(std::make_unique<Model>(modelType, modelDesc, materialsGPU));

		}

		//レンダーステートキャッシュに登録
		renderStatesCache.append_range(modelRenderStates_);

		return modelUniques;
	}


	//PSO生成時に必要
	std::vector<RenderState> const& WatchRenderStateCache(AgentKey key_)const;
	//↑を呼出し後、キャッシュは削除してほしい
	void DeleteRenderStateCache(NexusFieldProof proof_, AgentKey key_);

private:

	ModelDescParts AssembleModelDescParts
	(
		std::string const& modelFileName_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& inputMaterials_
	);

	//生成数。ネーミング用
	UINT numCreate{};
	//モデルディスク組み立て役
	std::unique_ptr<ModelDescAssembler> modelDescAssembler;
	//PSO生成時に生成された全モデルのレンダーステートパターンが必要
	std::vector<RenderState> renderStatesCache;

	
};

