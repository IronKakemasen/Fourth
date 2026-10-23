#pragma once
#include "SceneExecutionAgent.h"


template<typename... SceneTypes>
class aFourth;

class RenderContext;

struct SceneContext::ExecutionAgent::RenderContextProof
{
private:
	friend class RenderContext;

	explicit RenderContextProof() = default;
};

struct SceneContext::ExecutionAgent::EngineInterfaceProof
{
private:
	template<typename... SceneTypes>
	friend class aFourth;

	explicit EngineInterfaceProof() = default;

};