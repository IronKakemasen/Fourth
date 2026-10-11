#pragma once
#include "../../SceneContext.h"

class SceneContext::ExecutionAgent
{

public:

	ExecutionAgent(NexusFieldProof proof_, SceneController& sceneController_);

	void RunSceneController(NexusFieldProof proof_);

private:

	SceneController& sceneController;
};

