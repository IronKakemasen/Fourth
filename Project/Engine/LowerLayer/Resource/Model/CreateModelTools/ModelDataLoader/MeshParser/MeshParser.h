#pragma once
#include "../ModelDataLoader.h"

struct ResourceMesh;
struct aiMesh;


class ModelContext::ModelDataLoader::MeshParser
{
	friend class ModelContext::ModelDataLoader;

	static void ParseMesh(ResourceMesh& dstMesh_, const aiMesh* pSrcMesh_);
};

