#pragma once
#include "../../ModelDataCreator.h"
#include "../../../ModelSlotAllocator/ModelSlotAllocator.h"

//外部
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"


class MeshContext::ModelDataCreator::MeshDataSRVHeapIndexGroupContainerBufferCreator
{
	friend class MeshContext::ModelDataCreator;

	static void Create
	(
		const std::vector<StructuredBufferDataDefinition::MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		BufferContext::BufferDispatcher* dispatcher_,
		MeshContext::ModelSlotAllocator* allocator_
	);
};

