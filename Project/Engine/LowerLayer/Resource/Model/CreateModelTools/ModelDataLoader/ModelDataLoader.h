#pragma once
#include "../../ModelContext.h"

struct ModelData;
struct aiScene;

class ModelContext::ModelDataLoader
{
public:

	ModelDataLoader(NexusFieldProof proof_);
	~ModelDataLoader();

	///ファイルの名前から実メッシュデータのアドレスを生成
	///既に読み込み済みの場合はアサートで止める
	ModelData* Load(std::string fileName_ , std::string filePath_);


private:

	class ModelDataCache;
	class MeshParser;
	class MaterialParser;

	std::unique_ptr<ModelDataCache> modelDataCache;
	//シーンデータ
	const aiScene* scene = nullptr;   


};

