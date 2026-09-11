#pragma once
#include "../../WindowContext.h"

class WindowContext::ExecutionAgent
{
public:
	ExecutionAgent(NexusFieldProof proof_, WindowContext& windowContext_);

	void WindowContextFinalize(NexusFieldProof proof_);

private:
	WindowContext& windowContext;
};

