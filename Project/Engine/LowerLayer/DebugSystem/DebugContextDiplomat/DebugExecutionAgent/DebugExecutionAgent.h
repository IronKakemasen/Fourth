#pragma once
#include "../../DebugContext.h"

class DebugContext::ExecutionAgent
{
public:

	ExecutionAgent(NexusFieldProof proof_, DebugContext& debugContext_);

	void InstantiateImguiDebugger
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

private:

	DebugContext& debugContext;
};

