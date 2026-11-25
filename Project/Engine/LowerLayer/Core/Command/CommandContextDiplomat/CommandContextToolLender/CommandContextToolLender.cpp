#include "PreCompileHeader.h"
#include "CommandContextToolLender.h"


CommandContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	ID3D12CommandQueue& cmdQueue_,
	ID3D12GraphicsCommandList6& cmdList_,
	RuntimeWrapper& runtimeWrapper_
)
{
	std::get<ID3D12CommandQueue*>(tools) = &cmdQueue_;
	std::get<RuntimeWrapper*>(tools) = &runtimeWrapper_;
	std::get<ID3D12GraphicsCommandList6*>(tools) = &cmdList_;

}