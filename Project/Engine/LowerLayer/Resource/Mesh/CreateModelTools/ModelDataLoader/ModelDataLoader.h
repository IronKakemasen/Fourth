#pragma once
#include "../ModelDataCreator/ModelDataCreator.h"


#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"
#include ".././../../../External/assimp/include/assimp/cimport.h"


struct ResourceMesh;
struct ResourceMaterial;
struct ModelDataAggregate;


class MeshContext::ModelDataCreator::ModelDataLoader
{
public:

	ModelDataLoader(MeshContext::InstanceKey key_);
	~ModelDataLoader();

	///ファイルの名前から実メッシュデータのアドレスを生成
	///既に読み込み済みの場合はぬるぽを返す
	ModelDataAggregate* Load(std::string fileName_ , std::string filePath_);

private:

	class ModelDataCache;

	std::unique_ptr<ModelDataCache> modelDataCache;
	//シーンデータ
	const aiScene* scene = nullptr;   

	std::wstring Convert(const aiString& path);

	void ParseMesh(ResourceMesh& dstMesh_, const aiMesh* pSrcMesh_);
	void ParseMaterial(ResourceMaterial& dstMaterial_, const aiMaterial* pSrcMaterial_);


};

