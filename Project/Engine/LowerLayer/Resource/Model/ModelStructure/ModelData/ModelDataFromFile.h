#pragma once
#include "../../ModelContext.h"

//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/Material.h"


struct ModelContext::ModelDataFromFile
{
	std::vector<StructuredBufferModelData::MeshCPU> resourceMesh;
	std::vector<Material::StandardCPU> resourceMaterial;
};

