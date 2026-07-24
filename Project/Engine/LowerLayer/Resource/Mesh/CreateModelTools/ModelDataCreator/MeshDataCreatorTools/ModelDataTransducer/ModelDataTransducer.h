#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"


struct StandardVertex;

class MeshContext::ModelDataCreator::DataTransducer
{
	friend class MeshContext::ModelDataCreator;

	//CPU用の頂点データをGPU用に移し替える
	[[nodiscard]] static std::vector<StructuredBufferDataDefinition::StandardVertexGPU> 
		TransferVertexDataTypeToGPU(const std::vector<StandardVertex>& vertices_);
		
};

