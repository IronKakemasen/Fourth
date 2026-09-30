#include "PreCompileHeader.h"
#include "CommandContextToolLender.h"


CommandContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	ID3D12CommandQueue* cmdQueue_,
	RuntimeWrapper* runtimeWrapper_
)
{
	std::get<ID3D12CommandQueue*>(tools) = cmdQueue_;
	std::get<RuntimeWrapper*>(tools) = runtimeWrapper_;

}