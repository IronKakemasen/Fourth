#pragma once
#include "../ImGuiDebugger.h"

class DebugContext::ImGuiDebugger::SetUpper
{
	friend class ImGuiDebugger;

	void InitializeImGui
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

};

