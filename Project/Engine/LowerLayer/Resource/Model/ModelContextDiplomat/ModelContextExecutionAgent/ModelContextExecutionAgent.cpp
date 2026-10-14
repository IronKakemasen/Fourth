#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "ModelAgentLicences.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"
#include "../../CreateModelTools/ModelCreator.h"


ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext& modelContext_,
	ModelDataBatcher& modelDataBatcher_,
	ModelCreator& modelCreator_
):modelContext(modelContext_), modelDataBatcher(modelDataBatcher_), modelCreator(modelCreator_)
{
	
}


void ModelContext::ExecutionAgent::DeleteModelDataCache(NexusFieldProof proof_)
{
	modelContext.DeleteModelDataCache(proof_, AgentKey{});
	modelCreator.DeleteRenderStateCache(proof_, AgentKey{});
}


void ModelContext::ExecutionAgent::BatchModelData
(
	SceneContextProof proof_,
	UINT const frameIndex_,
	std::vector<Model*> const& models_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	modelDataBatcher.BatchModelData
	(
		AgentKey{},
		frameIndex_,
		models_,
		bufferContextDiplomat_
	);
}

std::vector<RenderState> const& ModelContext::ExecutionAgent::WatchRenderStateCache(RenderContextProof proof_)const
{
	return modelCreator.WatchRenderStateCache(AgentKey{});
}

