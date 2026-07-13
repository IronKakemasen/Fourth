#pragma once
#include "../ModelCreator.h"

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

	//モデル登録ファイルから何が登録されているか読み込む
	void LoadModelRegistry(std::string const registryFilePath_);

};

