#include "PreCompileHeader.h"
#include "ModelDataCache.h"


MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::ModelDataCache(MeshContext::InstanceKey key_)
{

}

std::optional<ModelDataAggregate> MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::FindDuplication(AccessKey key_, std::string fileName_)
{
	if (modelDataCache.find(fileName_) != modelDataCache.end())
	{				
		return modelDataCache.at(fileName_);
	}

	return std::nullopt;
}

void MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::Register(AccessKey key_, std::string fileName_, const ModelDataAggregate& data_)
{
	Logger::Log("Regieter: " + fileName_, "ModelDataCache.cpp");

	modelDataCache[fileName_] = data_;
}
