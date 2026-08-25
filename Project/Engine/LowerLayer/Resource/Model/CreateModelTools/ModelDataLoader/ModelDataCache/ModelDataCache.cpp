#include "PreCompileHeader.h"
#include "ModelDataCache.h"
#include "../../../ModelStructure/ModelData/ModelDataAggregate.h"


ModelContext::ModelDataLoader::ModelDataCache::ModelDataCache(NexusFieldProof proof_)
{

}

ModelContext::ModelDataLoader::ModelDataCache::~ModelDataCache()
{
	Logger::Log("ModelDataCache Destructor runs", "ModelDataCache.cpp");
	Logger::Log("Delete modelData cache", "ModelDataCache.cpp");
}

void ModelContext::ModelDataLoader::ModelDataCache::FindDuplication(AccessKey key_, std::string fileName_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		modelDataCache.find(fileName_) == modelDataCache.end(),
		"おかしいね、ファイルを2重に読み込んでる",
		"ModelDataCache.cpp"
	);

}

void ModelContext::ModelDataLoader::ModelDataCache::StoreTemporarily(AccessKey key_, std::string fileName_, std::unique_ptr<ModelDataAggregate>&& data_)
{
	Logger::Log("Regieter: " + fileName_, "ModelDataCache.cpp");

	modelDataCache[fileName_] = std::move(data_);
}
