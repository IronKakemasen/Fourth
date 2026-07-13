#pragma once
#include "../ModelDataLoader.h"
#include "../../../ModelStructure/ModelData/ModelData.h"

class MeshContext::ModelCreator::ModelDataLoader::ModelDataCache
{
public:

	struct AccessKey;

	ModelDataCache(MeshContext::InstanceKey key_);

	std::optional<ModelData> FindDuplication(AccessKey key_, std::string fileName_);
	void Register(AccessKey key_, std::string fileName_, const ModelData& data_);

private:

	std::unordered_map<std::string, ModelData> modelDataCache;
};

struct MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::AccessKey
{
private:
	friend class MeshContext::ModelCreator::ModelDataLoader;
	explicit AccessKey() = default;
};

