#include "PreCompileHeader.h"
#include "ModelDataLoader.h"

#include "ModelDataCache/ModelDataCache.h"

MeshContext::ModelDataLoader::ModelDataLoader(MeshContext::InstanceKey key_)
{
	modelDataCache.reset(new ModelDataCache(key_));
}

MeshContext::ModelDataLoader::~ModelDataLoader()
{

}

void MeshContext::ModelDataLoader::Load
(
	std::string fileName_,
	std::vector<ResourceMesh>& meshes_,
	std::vector<ResourceMaterial>& materials_
)
{
	//キャッシュにあるか確認
	std::optional<ModelData> cachedModelData = modelDataCache->FindDuplication(ModelDataCache::AccessKey{},fileName_);
	if (cachedModelData)
	{
		meshes_ = cachedModelData->resourceMesh;
		materials_ = cachedModelData->resourceMaterial;

		return;
	}
}
