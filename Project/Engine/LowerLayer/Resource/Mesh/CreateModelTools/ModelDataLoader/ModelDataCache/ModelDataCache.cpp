#include "PreCompileHeader.h"
#include "ModelDataCache.h"


MeshContext::ModelDataLoader::ModelDataCache::ModelDataCache(MeshContext::InstanceKey key_)
{

}

ModelDataAggregate* MeshContext::ModelDataLoader::ModelDataCache::FindDuplication(AccessKey key_, std::string fileName_)
{
	if (modelDataCache.find(fileName_) != modelDataCache.end())
	{				
		return modelDataCache.at(fileName_).get();
	}

	return nullptr;
}

void MeshContext::ModelDataLoader::ModelDataCache::Register(AccessKey key_, std::string fileName_, std::unique_ptr<ModelDataAggregate>&& data_)
{
	Logger::Log("Regieter: " + fileName_, "ModelDataCache.cpp");

	modelDataCache[fileName_] = std::move(data_);
}
