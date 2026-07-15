#pragma once
#include "../ModelDataLoader.h"
#include "../../../ModelStructure/ModelData/ModelDataAggregate.h"

class MeshContext::ModelCreator::ModelDataLoader::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(MeshContext::InstanceKey key_);

	std::shared_ptr<ModelDataAggregate> FindDuplication(AccessKey key_, std::string fileName_);
	void Register(AccessKey key_, std::string fileName_, std::shared_ptr<ModelDataAggregate> data_);

private:

	std::unordered_map<std::string, std::shared_ptr<ModelDataAggregate>> modelDataCache;
};

struct MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::AccessKey
{
private:
	friend class MeshContext::ModelCreator::ModelDataLoader;
	explicit AccessKey() = default;
};

