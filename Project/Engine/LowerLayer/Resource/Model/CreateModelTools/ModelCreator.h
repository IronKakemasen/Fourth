#pragma once
#include "../ModelContext.h"
#include "../ModelStructure/Model.h"


//外部
//パフォーマンスのため
#include "../../Material/MaterialContext.h"


class ModelContext::ModelCreator
{
	class ModelDescAssembler;

	using ModelDescParts = std::tuple
	<
		std::vector<ConstantBuffers::ModelConstantsCPUGPU>,
		std::vector<Material::StandardGPU>,
		std::vector<size_t>
	>;

public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		ModelSlotAllocator& slotAllocator_,
		TextureContextDiplomat& textureContextDiplomat_,
		MaterialContextDiplomat& materialContextDiplomat_
	);

	~ModelCreator();

	template<Model::MeshUpdateType type>
	std::vector<std::unique_ptr<Model>> Create
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		UINT const numCreate_,
		std::string const& modelName_
	);


	//PSO生成時に必要
	std::vector<RenderState> const& WatchRenderStateCache(AgentKey key_)const;
	//↑を呼出し後、renderStatesCacheは削除
	void DeleteRenderStateCache(NexusFieldProof proof_, AgentKey key_);

private:

	ModelDescParts AssembleModelDescParts
	(
		std::string const& modelFileName_
	);

	//生成数。ネーミング用
	UINT numCreate{};
	//モデルディスク組み立て役
	std::unique_ptr<ModelDescAssembler> modelDescAssembler;
	//PSO生成時に生成された全モデルのレンダーステートパターンが必要
	std::vector<RenderState> renderStatesCache;
	//モデルに必須のマテリアルをアタッチする
	MaterialContext::MaterialAttacher* materialAttacher;
	
};

