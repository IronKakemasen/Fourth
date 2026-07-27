#pragma once
#include "../../ModelDataCreator.h"
#include "../../../ModelSlotAllocator/ModelSlotAllocator.h"

//外部
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"


class ModelContext::ModelDataCreator::MeshDataSRVHeapIndexGroupContainerBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	static void Create
	(
		const std::vector<StructuredBufferDataDefinition::MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		BufferContext::BufferDispatcher* dispatcher_,
		BufferContext::BufferUploader* uploader_,
		ModelContext::ModelSlotAllocator* allocator_
	);
};

