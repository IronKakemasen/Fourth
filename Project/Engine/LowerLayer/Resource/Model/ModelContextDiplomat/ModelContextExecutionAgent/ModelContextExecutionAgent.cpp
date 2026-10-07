#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "../../ModelContainer/ModelContainer.h"
#include "../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"


ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext& modelContext_,
	ModelContainer& modelContainer_,
	ModelDataBatcher& modelDataBatcher_
):modelContext(modelContext_), modelContainer(modelContainer_), modelDataBatcher(modelDataBatcher_)
{
	
}


void ModelContext::ExecutionAgent::DeleteModelDataCache(NexusFieldProof proof_)
{
	modelContext.DeleteModelDataCache(proof_, AgentKey{});
}

void ModelContext::ExecutionAgent::SeparateModelContainer(NexusFieldProof proof_)
{
	modelContainer.SeparateModels(proof_, AgentKey{});
}

void ModelContext::ExecutionAgent::BatchStaticModelData
(
	NexusFieldProof proof_,
	UINT const frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	modelDataBatcher.BatchModelData<Model::Type::kStatic>
	(
		proof_,
		AgentKey{},
		modelContainer,
		frameIndex_,
		bufferContextDiplomat_
	);
}

void ModelContext::ExecutionAgent::BatchDynamicModelData
(
	NexusFieldProof proof_,
	UINT const frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	modelDataBatcher.BatchModelData<Model::Type::kDynamic>
	(
		proof_,
		AgentKey{},
		modelContainer,
		frameIndex_,
		bufferContextDiplomat_
	);

}
