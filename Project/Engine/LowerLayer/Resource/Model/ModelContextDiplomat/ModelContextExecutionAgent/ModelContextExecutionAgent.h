#pragma once
#include "../../ModelContext.h"

class Model;
struct RenderState;

class ModelContext::ExecutionAgent
{
public:

	struct SceneContextProof;
	struct RenderContextProof;

	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext& modelContext_,
		ModelDataBatcher& modelDataBatcher_,
		ModelCreator& modelCreator_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);
	
	//モデルデータをバッチングする
	void BatchModelData
	(
		SceneContextProof proof_,
		UINT const frameIndex_,
		std::vector<Model*> const& models_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	std::vector<RenderState> const& WatchRenderStateCache(RenderContextProof proof_)const;


private:

	ModelContext& modelContext;
	ModelDataBatcher& modelDataBatcher;
	ModelCreator& modelCreator;
};


