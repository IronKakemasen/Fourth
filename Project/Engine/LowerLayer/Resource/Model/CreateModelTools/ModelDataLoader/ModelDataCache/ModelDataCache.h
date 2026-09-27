#pragma once
#include "../ModelDataLoader.h"


class ModelContext::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(NexusFieldProof proof_);
	~ModelDataCache();

	//ダブりチェック
	void FindDuplication(AccessKey key_, std::string const& fileName_);
	//一時データとして保存
	void StoreTemporarily(AccessKey key_, std::string const& fileName_, std::unique_ptr<ModelDataFromFile>&& data_);

private:

	std::unordered_map<std::string, std::unique_ptr<ModelDataFromFile>> modelDataCache;
};

struct ModelContext::ModelDataCache::AccessKey
{
private:
	friend class ModelContext::ModelDataLoader;
	explicit AccessKey() = default;
};

