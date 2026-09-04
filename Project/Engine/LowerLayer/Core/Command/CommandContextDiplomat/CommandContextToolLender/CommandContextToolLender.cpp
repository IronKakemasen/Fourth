#include "PreCompileHeader.h"
#include "CommandContextToolLender.h"


CommandContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	ID3D12CommandQueue* cmdQueue_
)
{
	std::get<ID3D12CommandQueue*>(tools) = cmdQueue_;

}