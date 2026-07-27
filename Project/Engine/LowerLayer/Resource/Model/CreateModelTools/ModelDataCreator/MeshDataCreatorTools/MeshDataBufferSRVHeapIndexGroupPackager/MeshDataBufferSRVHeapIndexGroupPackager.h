#pragma once
#include "../../ModelDataCreator.h"


//外部
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"


class ModelContext::ModelDataCreator::MeshDataBufferSRVHeapIndexGroupPackager
{
	friend class ModelContext::ModelDataCreator;

	static void PackMeshDataBufferSRVHeapIndex
	(
		const std::vector<MeshDataBufferUniqueIDGroup>& uniqueIDGroupContainer_,
		std::vector<StructuredBufferDataDefinition::MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
		BufferContext::BufferDispatcher* dispatcher_
	);

};

