#pragma once
#include "../../ModelContext.h"

//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"

struct ModelContext::ModelDataFromFile
{
	std::vector<StructuredBufferModelData::MeshCPU> resourceMesh;
	std::vector<StructuredBufferModelData::MaterialCPU> resourceMaterial;
};

