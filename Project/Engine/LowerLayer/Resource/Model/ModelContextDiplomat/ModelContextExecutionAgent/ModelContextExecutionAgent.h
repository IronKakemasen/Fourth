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
		ModelCreator& modelCreator_,
		ModelFSDispatcher& modelFSDispatcher_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);
	
	//モデルデータをバッチングする。ループのコストが鼻につくので、
	//モデルのトランスフォームのアップデートもやっちゃう
	void BatchAndUpdateModelData
	(
		SceneContextProof proof_,
		UINT const frameIndex_,
		std::vector<Model*>& models_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//モデルクリエイターの所持する全レンダーステートパターンのキャッシュを見せる
	std::vector<RenderState> const& WatchRenderStateCache(RenderContextProof proof_)const;

	//シーンにModelFrontlineSystemsを割り当てる
	ModelFrontlineSystems* DispatchFrontSystems(SceneContextProof proof_);

private:

	ModelContext& modelContext;
	ModelDataBatcher& modelDataBatcher;
	ModelCreator& modelCreator;
	ModelFSDispatcher& modelFSDispatcher;
};


