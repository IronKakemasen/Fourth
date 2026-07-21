#include "PreCompileHeader.h"
#include "CommandContextToolLender.h"


CommandContext::ToolLender::ToolLender
(
	CommandContext::InstanceKey key_,
	ID3D12CommandQueue* cmdQueue_,
	CommandContext::ResourceUploader* resourceUploader_
)
{
	std::get<ID3D12CommandQueue*>(tools) = cmdQueue_;
	std::get<CommandContext::ResourceUploader*>(tools) = resourceUploader_;


	}