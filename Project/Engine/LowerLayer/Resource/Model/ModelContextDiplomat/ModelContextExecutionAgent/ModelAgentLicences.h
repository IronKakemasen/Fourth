#pragma once
#include "ModelContextExecutionAgent.h"

class SceneContext;
class RenderContext;

struct ModelContext::ExecutionAgent::SceneContextProof
{
private:
	friend class SceneContext;

	explicit SceneContextProof() = default;
};

struct ModelContext::ExecutionAgent::RenderContextProof
{
private:
	friend class RenderContext;

	explicit RenderContextProof() = default;
};


