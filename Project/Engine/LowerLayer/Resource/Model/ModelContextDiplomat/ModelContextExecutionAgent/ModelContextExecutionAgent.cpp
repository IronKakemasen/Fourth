#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "ModelAgentLicences.h"
#include "../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"
#include "../../CreateModelTools/ModelCreator.h"
#include "../../ModelFSDispatcher/ModelFSDispatcher.h"

ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext& modelContext_,
	ModelDataBatcher& modelDataBatcher_,
	ModelCreator& modelCreator_,
	ModelFSDispatcher& modelFSDispatcher_
):modelContext(modelContext_), modelDataBatcher(modelDataBatcher_), modelCreator(modelCreator_), modelFSDispatcher(modelFSDispatcher_)
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

ModelContext::ModelFrontlineSystems* ModelContext::ExecutionAgent::DispatchFrontSystems(SceneContextProof proof_)
{
	return modelFSDispatcher.Dispatch(AgentKey{});
}

