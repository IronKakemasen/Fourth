#pragma once
#include "../ModelDataLoader.h"


//外部
#include "../../../../../../../Assets/Shared/Material.h"

struct aiMaterial;
struct aiString;

class  ModelContext::ModelDataLoader::MaterialParser
{
	friend class ModelContext::ModelDataLoader;

	static void ParseMaterial(Material::StandardCPU& dstMaterial_, const aiMaterial* pSrcMaterial_);


	//以下ヘルパー
private:
	static std::string Convert(const aiString& path_);

};

