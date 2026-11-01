#pragma once
#include "GameObjectAgent.h"

class SceneContext;

struct GameObjectContext::ExecutionAgent::SceneContextProof
{
private:

	friend class SceneContext;

	explicit SceneContextProof() = default;
};
