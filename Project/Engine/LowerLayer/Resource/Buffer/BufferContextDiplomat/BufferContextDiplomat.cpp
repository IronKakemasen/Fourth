#include "PreCompileHeader.h"
#include "BufferContextDiplomat.h"
#include "BufferToolLender/BufferToolLender.h"


BufferContextDiplomat::BufferContextDiplomat
(
	BufferContext::InstanceKey key_,
	std::unique_ptr<BufferContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<BufferContext::ToolLender>>(tools) = std::move(toolLender_);
}
