#pragma once
#include "../../ModelContext.h"

struct aiScene;

class ModelContext::ModelDataLoader
{
public:

	ModelDataLoader(NexusFieldProof proof_, ModelDataCache& modelDataCache_);
	~ModelDataLoader();

	///ファイルの名前から実メッシュデータのアドレスを生成
	///既に読み込み済みの場合はアサートで止める
	ModelDataFromFile* Load(std::string const& fileName_ , std::string const& filePath_);


private:

	class MeshParser;
	class MaterialParser;

	ModelDataCache& modelDataCache;
	//シーンデータ
	const aiScene* scene = nullptr;   


};

