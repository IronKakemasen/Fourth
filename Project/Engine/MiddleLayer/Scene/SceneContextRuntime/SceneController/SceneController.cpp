#include "PreCompileHeader.h"
#include "SceneController.h"
#include "../../SceneLibrary/SceneLibrary.h"


SceneContext::ScenePipeline::SceneController::SceneController
(
	NexusFieldProof proof_,
	SceneLibrary& sceneLib_
):sceneLib(sceneLib_)
{

}


void SceneContext::ScenePipeline::SceneController::Run()
{
	curScene->Update();

}


void SceneContext::ScenePipeline::SceneController::ChangeScene(std::string const& next_)
{
	curScene = sceneLib.Export(next_);
	Logger::Log("Changed Scene To  " + next_, "SceneController.cpp");
}

SceneBehavior::Output const& SceneContext::ScenePipeline::SceneController::WatchCurrentSceneOutput()const
{
	return curScene->WatchSceneOutput();
}
