#include "PreCompileHeader.h"
#include "DebugContext.h"
#include "PrimaryDebugger/PrimaryDebugger.h"
#include "ImGuiDebugger/ImGuiDebugger.h"
#include "DebugContextDiplomat/DebugContextDiplomat.h"
#include "DebugContextDiplomat/DebugExecutionAgent/DebugExecutionAgent.h"



namespace
{
	auto const fileName = "DebugContext.cpp";
}

DebugContext::DebugContext
(
	NexusFieldProof proof_
)
{
	Logger::Entry("DebugContext: Constructor");

#ifdef _DEBUG

	primaryDebugger = std::make_unique<PrimaryDebugger>(proof_);
	Logger::Log("Instantiate: PrimaryDebugger", fileName);

#endif // DEBUG

	diplomat = std::make_unique<DebugContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *this,*imGuiDebugger)
	);
	Logger::End("DebugContext: DebugContextDiplomat");
	Logger::End("DebugContext: ExecutionAgent");


	Logger::End("DebugContext: Constructor");
}

void DebugContext::InstantiateImguiDebugger
(
	NexusFieldProof proof_,
	AgentKey key_,
	WindowContextDiplomat& windowContextDip_,
	DeviceContextDiplomat& deviceContextDip_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDip_
)
{
	imGuiDebugger = std::make_unique<ImGuiDebugger>
	(
		proof_,
		windowContextDip_,
		deviceContextDip_,
		descriptorHeapContextDip_
	);

	Logger::Log("Instantiate: ImGuiDebugger", fileName);

}


DebugContext::~DebugContext()
{

}
