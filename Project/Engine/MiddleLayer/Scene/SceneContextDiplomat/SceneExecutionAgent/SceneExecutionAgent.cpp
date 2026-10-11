#include "PreCompileHeader.h"
#include "SceneExecutionAgent.h"
#include "../../SceneContextRuntime/SceneController/SceneController.h"


SceneContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, SceneController& sceneController_)
	:sceneController(sceneController_)
{

}


void SceneContext::ExecutionAgent::RunSceneController(NexusFieldProof proof_)
{
	sceneController.Run(proof_, AgentKey{});
}
