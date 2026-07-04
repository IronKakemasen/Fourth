#include "PreCompileHeader.h"
#include "BufferDispatcher.h"


BufferContext::BufferDispatcher::BufferDispatcher
(
	BufferContext::InstanceKey key_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferContainer_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferContainer_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferContainer_,
	std::unordered_map<BufferUniqueID, std::pair<BufferContext::RegisterType, uint32_t>>* bufferLocationMap_
) :renderTargetBufferContainer(renderTargetBufferContainer_), computeBufferContainer(computeBufferContainer_), frameBufferContainer(frameBufferContainer_), bufferLocationMap(bufferLocationMap_)
{

}

