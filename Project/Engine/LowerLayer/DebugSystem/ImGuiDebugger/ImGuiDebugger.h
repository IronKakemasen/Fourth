#pragma once
#include "../DebugContext.h"


class DebugContext::ImGuiDebugger
{
	class SetUpper;

public:

	ImGuiDebugger
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

	void BeginNewFrame
	(
		NexusFieldProof proof_,
		AgentKey key_
	);

	void Render
	(
		AgentKey key_,
		CommandContextDiplomat& commandContextDiplomat_
	);

private:


};

