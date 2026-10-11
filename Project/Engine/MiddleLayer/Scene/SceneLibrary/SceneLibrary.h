#pragma once
#include "../SceneContext.h"

class SceneBehavior;

class SceneContext::SceneLibrary
{
public:

	SceneLibrary(NexusFieldProof proof_);

	void Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_);
	SceneBehavior* Export(std::string const& sceneName_);

private:

	std::unordered_map<std::string, std::unique_ptr<SceneBehavior>> sceneMap;
};

