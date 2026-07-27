#pragma once
#include "../../ModelDataCreator.h"

class ModelContext::ModelDataCreator::TransformMatrixContainerBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	static void Create
	(
		ModelContext::ModelSlotAllocator* slotAllocator_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		BufferContext::BufferDispatcher* bufferDispatcher_
	);

};

