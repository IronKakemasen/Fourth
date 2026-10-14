#pragma once
#include "ModelContextExecutionAgent.h"

class SceneContext;

struct ModelContext::ExecutionAgent::SceneContextProof
{
private:
	friend class SceneContext;

	explicit SceneContextProof() = default;
};