#include "PreCompileHeader.h"
#include "SceneController.h"
#include "../../SceneLibrary/SceneLibrary.h"


SceneContext::SceneController::SceneController
(
	NexusFieldProof proof_,
	SceneLibrary& sceneLib_
):sceneLib(sceneLib_)
{

}


void SceneContext::SceneController::Run(NexusFieldProof proof_, AgentKey key_)
{
	output = curScene->Update();

}


void SceneContext::SceneController::ChangeScene(std::string const& next_)
{
	curScene = sceneLib.Export(next_);
}