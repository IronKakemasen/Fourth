#pragma once
#include "../ModelDataLoader.h"

struct ModelData;

class ModelContext::ModelDataLoader::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(NexusFieldProof proof_);
	~ModelDataCache();

	//ダブりチェック
	void FindDuplication(AccessKey key_, std::string fileName_);
	//一時データとして保存
	void StoreTemporarily(AccessKey key_, std::string fileName_, std::unique_ptr<ModelData>&& data_);

private:

	std::unordered_map<std::string, std::unique_ptr<ModelData>> modelDataCache;
};

struct ModelContext::ModelDataLoader::ModelDataCache::AccessKey
{
private:
	friend class ModelContext::ModelDataLoader;
	explicit AccessKey() = default;
};

