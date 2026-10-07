#pragma once
#include "../../ModelContext.h"


class ModelContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext& modelContext_,
		ModelContainer& modelContainer_,
		ModelDataBatcher& modelDataBatcher_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);
	void SeparateModelContainer(NexusFieldProof proof_);
	
	//モデルクラスとの結合度を密にしたくないのでテンプレートにしません宣言
	void BatchStaticModelData
	(
		NexusFieldProof proof_,
		UINT const frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
	void BatchDynamicModelData
	(
		NexusFieldProof proof_,
		UINT const frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	ModelContext& modelContext;
	ModelContainer& modelContainer;
	ModelDataBatcher& modelDataBatcher;
};


