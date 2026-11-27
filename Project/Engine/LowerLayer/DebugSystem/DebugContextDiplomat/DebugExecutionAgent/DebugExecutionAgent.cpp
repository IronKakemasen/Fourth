#include "PreCompileHeader.h"
#include "DebugExecutionAgent.h"
#include "DebugAgentLicences.h"
#include "../../ImGuiDebugger/ImGuiDebugger.h"

DebugContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_, 
	DebugContext& debugContext_,
	ImGuiDebugger& imGuiDebugger_
):debugContext(debugContext_), imGuiDebugger(imGuiDebugger_)
{

}


void DebugContext::ExecutionAgent::InstantiateImguiDebugger
(
	NexusFieldProof proof_,
	WindowContextDiplomat& windowContextDip_,
	DeviceContextDiplomat& deviceContextDip_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDip_
)
{
	debugContext.InstantiateImguiDebugger
	(
		proof_,
		AgentKey{},
		windowContextDip_,
		deviceContextDip_,
		descriptorHeapContextDip_
	);
}

void DebugContext::ExecutionAgent::BeginImGuiNewFrame
(
	NexusFieldProof proof_
)
{
	imGuiDebugger.BeginNewFrame(proof_, AgentKey{});
}

void DebugContext::ExecutionAgent::RenderImGui
(
	RenderContextProof proof_,
	D3D12_GPU_DESCRIPTOR_HANDLE finalRefBufferGpuHandle_,
	CommandContextDiplomat& commandContextDiplomat_
)
{
	imGuiDebugger.Render(AgentKey{}, finalRefBufferGpuHandle_,commandContextDiplomat_);
}
