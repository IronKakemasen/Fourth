#include "PreCompileHeader.h"
#include "BufferToolLender.h"


BufferContext::ToolLender::ToolLender
(
	BufferContext::InstanceKey key_,
	BufferContext::BufferCreator* creator_,
	BufferContext::BufferUploader* uploader_,
	BufferContext::BufferDispatcher* dispatcher_,
	BufferContext::BufferCollector* collector_

)
{
	std::get<BufferContext::BufferCreator*>(tools) = creator_;
	std::get<BufferContext::BufferUploader*>(tools) = uploader_;
	std::get<BufferContext::BufferDispatcher*>(tools) = dispatcher_;
	std::get<BufferContext::BufferCollector*>(tools) = collector_;

}
