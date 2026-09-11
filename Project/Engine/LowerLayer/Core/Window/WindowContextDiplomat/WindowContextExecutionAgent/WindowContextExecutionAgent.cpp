#include "PreCompileHeader.h"
#include "WindowContextExecutionAgent.h"

WindowContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, WindowContext& windowContext_)
	:windowContext(windowContext_)
{

}


void WindowContext::ExecutionAgent::WindowContextFinalize(NexusFieldProof proof_)
{
	windowContext.Finalize(proof_, AgentKey{});
}
