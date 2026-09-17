#pragma once
#include "../ModelDataCreator.h"

//外部
#include "../../../../../../../Assets/Shared/StructuredBufferModelData.h"


class ModelContext::ModelDataCreator::MeshDataBufferSRVHeapIndexGroupPackager
{
	friend class ModelContext::ModelDataCreator;

	static void PackMeshDataBufferSRVHeapIndex
	(
		const std::vector<MeshDataBufferUniqueIDGroup>& uniqueIDGroupContainer_,
		std::vector<StructuredBufferModelData::MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
		BufferContext::BufferDispatcher* dispatcher_
	);

};

