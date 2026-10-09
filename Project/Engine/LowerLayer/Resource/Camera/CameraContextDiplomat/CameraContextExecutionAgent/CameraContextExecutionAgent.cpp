#include "PreCompileHeader.h"
#include "CameraContextExecutionAgent.h"
#include "../../CameraFSDispatcher/CameraFSDispatcher.h"


CameraContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	FrontlineSystemsDispatcher& frontlineSystemsDispatcher_
):frontlineSystemsDispatcher(frontlineSystemsDispatcher_)
{

}


CameraContext::CameraFrontlineSystems* CameraContext::ExecutionAgent::DispatchFrontlineSystems(SceneContextProof proof_)
{
	return frontlineSystemsDispatcher.Dispatch(AgentKey{});
}
