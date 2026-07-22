#pragma once
#include "../ModelDataLoader.h"


struct aiMaterial;
struct ResourceMaterial;
struct aiString;

class  MeshContext::ModelDataLoader::MaterialParser
{
	friend class MeshContext::ModelDataLoader;

	static void ParseMaterial(ResourceMaterial& dstMaterial_, const aiMaterial* pSrcMaterial_);

	static std::wstring Convert(const aiString& path_);

};

