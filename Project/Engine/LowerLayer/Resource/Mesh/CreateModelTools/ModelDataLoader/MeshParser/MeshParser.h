#pragma once
#include "../ModelDataLoader.h"

struct ResourceMesh;
struct aiMesh;


class MeshContext::ModelDataLoader::MeshParser
{
	friend class MeshContext::ModelDataLoader;

	static void ParseMesh(ResourceMesh& dstMesh_, const aiMesh* pSrcMesh_);
};

