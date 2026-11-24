#include "PreCompileHeader.h"
#include "DebugExecutionAgent.h"

DebugContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, DebugContext& debugContext_)
	:debugContext(debugContext_)
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
