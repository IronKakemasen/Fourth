#include "PreCompileHeader.h"
#include "SwapChainExecutionAgent.h"
#include "../../Presenter/Presenter.h"


SwapChainContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, Presenter& presenter_)
	:presenter(presenter_)
{

}

UINT SwapChainContext::ExecutionAgent::GetFrameIndex(NexusFieldProof proof_)const
{
	return presenter.GetFrameIndex(proof_, AgentKey{});
}


void SwapChainContext::ExecutionAgent::Present(NexusFieldProof proof_)const
{
	presenter.Present();
}

