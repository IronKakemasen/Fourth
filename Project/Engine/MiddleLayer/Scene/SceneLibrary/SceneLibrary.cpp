#include "PreCompileHeader.h"
#include "SceneLibrary.h"
#include "../SceneStructure/SceneBehavior.h"

namespace
{
	auto const fileName = "SceneLibrary.cpp";
}

SceneContext::SceneLibrary::SceneLibrary(NexusFieldProof proof_)
{

}


void SceneContext::SceneLibrary::Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		sceneMap.find(sceneName_) == sceneMap.end(),
		sceneName_ + "←名前被りです",
		fileName
	);

	Logger::Log("Import Scene: " + sceneName_, fileName);
	sceneMap[sceneName_] = std::move(scene_);
}

SceneBehavior* SceneContext::SceneLibrary::Export(std::string const& sceneName_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		sceneMap.find(sceneName_) != sceneMap.end(),
		sceneName_ + "こんななまえのSceneは作成されていない",
		fileName
	);

	return sceneMap[sceneName_].get();
}
