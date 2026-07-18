#include "PreCompileHeader.h"
#include "BufferToolLender.h"


BufferContext::ToolLender::ToolLender
(
	BufferContext::InstanceKey key_,
	BufferContext::BufferCreator* creator_,
	BufferContext::BufferUploader* uploader_
)
{
	std::get<BufferContext::BufferCreator*>(tools) = creator_;
	std::get<BufferContext::BufferUploader*>(tools) = uploader_;

}
