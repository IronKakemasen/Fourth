#pragma once
#include "../../BufferContext.h"


class GPUBufferBehavior;

class BufferContext::BufferDispatcher
{
public:

	BufferDispatcher
	(
		BufferContext::InstanceKey key_,
		BufferContext::BufferPoolSet* bufferPoolSet_
	);

	///ユニークIDをもとに目的のバッファを倉庫から渡します
	[[nodiscard]] inline GPUBufferBehavior* Dispatch(BufferUniqueID bufferID_)
	{
		auto& idToType_location = bufferPoolSet->bufferLocationMap[bufferID_];

		BufferContext::RegisterType dstRegisterType = idToType_location.first;
		uint32_t dstPoolIndex = idToType_location.second;

		return bufferPoolSet->ContainerTable(dstRegisterType)->at(dstPoolIndex).get();
	}

private:

	///倉庫
	BufferContext::BufferPoolSet* bufferPoolSet;
};
