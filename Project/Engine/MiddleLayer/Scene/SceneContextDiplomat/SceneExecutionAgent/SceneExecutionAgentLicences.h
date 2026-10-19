#pragma once
#include "SceneExecutionAgent.h"


template<typename... SceneTypes>
class aFourth;

struct SceneContext::ExecutionAgent::EngineInterfaceProof
{
private:
	template<typename... SceneTypes>
	friend class aFourth;

	explicit EngineInterfaceProof() = default;

};