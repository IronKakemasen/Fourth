#pragma once
#include "../ModelDataLoader.h"

//外部
#include "../../../../../../../Assets/Shared/StructuredBufferModelData.h"

struct aiMesh;


class ModelContext::ModelDataLoader::MeshParser
{
	friend class ModelContext::ModelDataLoader;

	static void ParseMesh(StructuredBufferModelData::MeshCPU& dstMesh_, const aiMesh* pSrcMesh_);
};

