#include "PreCompileHeader.h"
#include "ModelDataLoader.h"

#include "ModelDataCache/ModelDataCache.h"

namespace
{
    auto const fileName = "ModelDataLoader.cpp";
}

MeshContext::ModelCreator::ModelDataLoader::ModelDataLoader(MeshContext::InstanceKey key_)
{
    Logger::Entry("ModelDataLoader: Constructor");

    std::string const registryFilePath = "Assets/Registry/ModelFiles.txt";

    LoadModelRegistry(registryFilePath);
    Logger::Log("Load: " + registryFilePath, fileName);

	modelDataCache.reset(new ModelDataCache(key_));
    Logger::Log("Instantiate: ModelDataCache",fileName);

    Logger::End("ModelDataLoader: Constructor");
}

MeshContext::ModelCreator::ModelDataLoader::~ModelDataLoader()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshContext::ModelCreator::ModelDataLoader::Load
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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshContext::ModelCreator::ModelDataLoader::LoadModelRegistry(std::string const registryFilePath_)
{
    std::ifstream file(registryFilePath_);
    ErrorMessageOutput::Abort::DetectError
    (
        file.is_open(),
        registryFilePath_ + "このパス無くない？",
        fileName
    );

    std::string line;

    while (std::getline(file, line))
    {
        constexpr std::string_view keyToken = "key: \"";
        constexpr std::string_view valueToken = "value: \"";

        auto keyStart = line.find(keyToken);
        if (keyStart == std::string::npos)
        {
            continue;
        }


        keyStart += keyToken.size();

        auto keyEnd = line.find("\"", keyStart);
        if (keyEnd == std::string::npos)
        {
            continue;
        }


        std::string key = line.substr
        (
            keyStart,
            keyEnd - keyStart
        );


        auto valueStart = line.find(valueToken);
        if (valueStart == std::string::npos)
        {
            continue;
        }


        valueStart += valueToken.size();

        auto valueEnd = line.find("\"", valueStart);
        if (valueEnd == std::string::npos)
        {
            continue;
        }


        std::string value = line.substr
        (
            valueStart,
            valueEnd - valueStart
        );


        modelFileName_pathLib.emplace(key,value);
    }

}
