#pragma once
#include "../../ModelContext.h"

class Model;

class ModelContext::ExecutionAgent
{
public:

	struct SceneContextProof;

	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext& modelContext_,
		ModelDataBatcher& modelDataBatcher_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);
	
	//モデルクラスとの結合度を密にしたくないのでテンプレートにしません宣言
	void BatchModelData
	(
		SceneContextProof proof_,
		UINT const frameIndex_,
		std::vector<Model*> const& modelsStatic_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	ModelContext& modelContext;
	ModelDataBatcher& modelDataBatcher;
};


