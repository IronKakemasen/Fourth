#include "PreCompileHeader.h"
#include "BufferToolLender.h"


BufferContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	BufferCreator* creator_,
	BufferUploader* uploader_,
	BufferDispatcher* dispatcher_,
	BufferCollector* collector_,
	WorldConstantBuffers* worldConstantBuffers_

)
{
	std::get<BufferCreator*>(tools) = creator_;
	std::get<BufferUploader*>(tools) = uploader_;
	std::get<BufferDispatcher*>(tools) = dispatcher_;
	std::get<BufferCollector*>(tools) = collector_;
	std::get<WorldConstantBuffers*>(tools) = worldConstantBuffers_;

}
