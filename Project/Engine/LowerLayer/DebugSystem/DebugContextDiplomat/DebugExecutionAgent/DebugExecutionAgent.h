#pragma once
#include "../../DebugContext.h"

class DebugContext::ExecutionAgent
{
public:

	struct RenderContextProof;

	ExecutionAgent
	(
		NexusFieldProof proof_,
		DebugContext& debugContext_,
		ImGuiDebugger& imGuiDebugger_
	);

	void InstantiateImguiDebugger
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

	void BeginImGuiNewFrame
	(
		NexusFieldProof proof_
	);

	void RenderImGui
	(
		RenderContextProof proof_,
		CommandContextDiplomat& commandContextDiplomat_
	);

private:

	DebugContext& debugContext;
	ImGuiDebugger& imGuiDebugger;

};

