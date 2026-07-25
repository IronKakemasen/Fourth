#pragma once
#include "../ModelDataLoader.h"

struct ModelDataAggregate;

class MeshContext::ModelDataLoader::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(NexusFieldProof proof_);

	//ダブりチェック
	void FindDuplication(AccessKey key_, std::string fileName_);
	//一時データとして保存
	void StoreTemporarily(AccessKey key_, std::string fileName_, std::unique_ptr<ModelDataAggregate>&& data_);

private:

	std::unordered_map<std::string, std::unique_ptr<ModelDataAggregate>> modelDataCache;
};

struct MeshContext::ModelDataLoader::ModelDataCache::AccessKey
{
private:
	friend class MeshContext::ModelDataLoader;
	explicit AccessKey() = default;
};

