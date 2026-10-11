#include "PreCompileHeader.h"
#include "SceneCreator.h"
#include "../SceneLibrary/SceneLibrary.h"


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextDiplomat.h"
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextExecutionAgent/CameraContextExecutionAgent.h"
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextExecutionAgent/CameraContextAgentLicences.h"
#include "../../../LowerLayer/Resource/Camera/CameraFSDispatcher/CameraFSDispatcher.h"



SceneContext::SceneCreator::SceneCreator(NexusFieldProof proof_, SceneLibrary& sceneLib_)
	:sceneLib(sceneLib_)
{

}

void SceneContext::SceneCreator::Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_)
{
	sceneLib.Import(std::move(scene_), sceneName_);
}


CameraContext::CameraFrontlineSystems* SceneContext::SceneCreator::ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_)
{
	//CameraFrontlineSystemsを一つ渡してもらう
	auto agent = cameraContextDiplomat_.Access<CameraContext::ExecutionAgent>();
	
	return agent.DispatchFrontlineSystems(CameraContext::ExecutionAgent::SceneContextProof{});
}
