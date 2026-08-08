#pragma once
#include "../../ModelDataCreator.h"

//外部
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"
#include "../../../../../Buffer/BufferContextCmds.h"

class ModelContext::ModelDataCreator::MeshDataSRVHeapIndexGroupContainerBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	static void Create
	(
		const std::vector<StructuredBufferDataDefinition::MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferUploader* uploader_,
		BufferContextCmds::CreateCBufferCmd createCBufferCmd_
	);
};

