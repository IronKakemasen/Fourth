#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../../../../../Assets/Shared/StructuredBufferModelData.h"


struct StandardVertex;

class ModelContext::ModelDataCreator::DataTransducer
{
	friend class ModelContext::ModelDataCreator;

	//CPU用の頂点データをGPU用に移し替える
	[[nodiscard]] static std::vector<StructuredBufferModelData::StandardVertexGPU> 
		TransferVertexDataTypeToGPU(const std::vector<StructuredBufferModelData::StandardVertexCPU>& vertices_);
		
};

