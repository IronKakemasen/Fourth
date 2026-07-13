#include "PreCompileHeader.h"
#include "ModelDataCache.h"


MeshContext::ModelDataLoader::ModelDataCache::ModelDataCache(MeshContext::InstanceKey key_)
{

}

std::optional<ModelData> MeshContext::ModelDataLoader::ModelDataCache::FindDuplication(AccessKey key_, std::string fileName_)
{
	if (modelDataCache.find(fileName_) == modelDataCache.end())
	{
		Logger::Log("Regieter: " + fileName_, "ModelDataCache.cpp");
				
		//いちおうここでもチェック
		ErrorMessageOutput::Assert::DetectError
		(
			modelDataCache.contains(fileName_),
			fileName_ + "こんなファイルは存在しないぜ",
			"ModelDataCache.cpp"
		);

		return modelDataCache.at(fileName_);
	}

	return std::nullopt;
}

void MeshContext::ModelDataLoader::ModelDataCache::Register(AccessKey key_, std::string fileName_, const ModelData& data_)
{
	modelDataCache[fileName_] = data_;
}
