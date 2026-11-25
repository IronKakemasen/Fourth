#pragma once
#include "DebugExecutionAgent.h"

class RenderContext;


struct DebugContext::ExecutionAgent::RenderContextProof
{
private:

	friend class RenderContext;
	explicit RenderContextProof() = default;
};



