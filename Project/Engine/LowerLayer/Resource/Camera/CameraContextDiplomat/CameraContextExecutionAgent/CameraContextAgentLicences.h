#pragma once
#include "CameraContextExecutionAgent.h"

class SceneContext;

struct CameraContext::ExecutionAgent::SceneContextProof
{
private:

	friend class SceneContext;
	explicit SceneContextProof() = default;

};


