#pragma once
#include "MaterialExecutionAgent.h"

class SceneContext;

struct MaterialContext::ExecutionAgent::SceneContextProof
{
private:

	friend class SceneContext;
	explicit SceneContextProof() = default;
};


