#include "PreCompileHeader.h"
#include "GameObjectAgent.h"
#include "../../ObjFSDispatcher/ObjFSDispatcher.h"
#include "GameObjectAgentLicences.h"


GameObjectContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, ObjFSDispatcher& objFSDispatcher_)
	:objFSDispatcher(objFSDispatcher_)
{

}

GameObjectContext::FrontlineSystems* GameObjectContext::ExecutionAgent::DispatchFrontlineSystems(SceneContextProof proof_)
{
	return objFSDispatcher.Dispatch(AgentKey{});
}
