#include "PreCompileHeader.h"
#include "ModelDataCache.h"
#include "../../../Model/ModelData/ModelDataAggregate.h"


MeshContext::ModelDataLoader::ModelDataCache::ModelDataCache(NexusFieldProof proof_)
{

}

void MeshContext::ModelDataLoader::ModelDataCache::FindDuplication(AccessKey key_, std::string fileName_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		modelDataCache.find(fileName_) == modelDataCache.end(),
		"おかしいね、ファイルを2重に読み込んでる",
		"ModelDataCache.cpp"
	);

}

void MeshContext::ModelDataLoader::ModelDataCache::StoreTemporarily(AccessKey key_, std::string fileName_, std::unique_ptr<ModelDataAggregate>&& data_)
{
	Logger::Log("Regieter: " + fileName_, "ModelDataCache.cpp");

	modelDataCache[fileName_] = std::move(data_);
}
