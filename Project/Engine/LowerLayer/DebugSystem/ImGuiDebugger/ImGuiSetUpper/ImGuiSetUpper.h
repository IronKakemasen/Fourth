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

private:

	static constexpr DXGI_FORMAT kImGuiRtvformat = DXGI_FORMAT_R8G8B8A8_UNORM;

};

