#pragma once
#include "../ModelCreator.h"


#include "../../.././../../External/assimp/include/assimp/Importer.hpp"
#include "../../.././../../External/assimp/include/assimp/scene.h"
#include "../../.././../../External/assimp/include/assimp/postprocess.h"
#include "../../.././../../External/assimp/include/assimp/cimport.h"



struct ResourceMesh;
struct ResourceMaterial;


class MeshContext::ModelCreator::ModelDataLoader
{
public:

	ModelDataLoader(MeshContext::InstanceKey key_);
	~ModelDataLoader();

	void Load
	(
		std::string fileName_,
		std::vector<ResourceMesh>& meshes_,
		std::vector<ResourceMaterial>& materials_
	);

private:

	class ModelDataCache;

	std::unique_ptr<ModelDataCache> modelDataCache;
	std::unordered_map<std::string, std::string > modelFileName_pathLib;
	//シーンデータ
	const aiScene* scene = nullptr;   

	//モデル登録ファイルから何が登録されているか読み込む
	void LoadModelRegistry(std::string const registryFilePath_);
	std::wstring Convert(const aiString& path);

	void ParseMesh(ResourceMesh& dstMesh_, const aiMesh* pSrcMesh_);
	void ParseMaterial(ResourceMaterial& dstMaterial_, const aiMaterial* pSrcMaterial_);


};

