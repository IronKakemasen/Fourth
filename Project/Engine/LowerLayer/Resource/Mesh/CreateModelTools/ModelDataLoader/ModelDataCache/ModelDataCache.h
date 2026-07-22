#pragma once
#include "../ModelDataLoader.h"
#include "../../../ModelStructure/ModelData/ModelDataAggregate.h"

class MeshContext::ModelDataCreator::ModelDataLoader::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(MeshContext::InstanceKey key_);

	ModelDataAggregate* FindDuplication(AccessKey key_, std::string fileName_);
	void Register(AccessKey key_, std::string fileName_, std::unique_ptr<ModelDataAggregate>&& data_);

private:

	std::unordered_map<std::string, std::unique_ptr<ModelDataAggregate>> modelDataCache;
};

struct MeshContext::ModelDataCreator::ModelDataLoader::ModelDataCache::AccessKey
{
private:
	friend class MeshContext::ModelDataCreator::ModelDataLoader;
	explicit AccessKey() = default;
};

