#include "PreCompileHeader.h"
#include "CameraContextExecutionAgent.h"
#include "CameraContextAgentLicences.h"
#include "../../CameraFSDispatcher/CameraFSDispatcher.h"
#include "../../CameraContextRuntime/CameraDataBatcher/CameraDataBatcher.h"

CameraContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	FrontlineSystemsDispatcher& frontlineSystemsDispatcher_,
	CameraDataBatcher& cameraDataBatcher_
):cameraDataBatcher(cameraDataBatcher_),frontlineSystemsDispatcher(frontlineSystemsDispatcher_)
{

}


CameraContext::FrontlineSystems* CameraContext::ExecutionAgent::DispatchFrontlineSystems(SceneContextProof proof_)
{
	return frontlineSystemsDispatcher.Dispatch(AgentKey{});
}

void CameraContext::ExecutionAgent::BatchCameraData
(
	SceneContextProof proof_,
	std::unordered_map<CameraSocket, CameraBehavior*> const& usingCamera_,
	UINT const frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	cameraDataBatcher.Batch(AgentKey{}, usingCamera_, frameIndex_, bufferContextDiplomat_);
}
