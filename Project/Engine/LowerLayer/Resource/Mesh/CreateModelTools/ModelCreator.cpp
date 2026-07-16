#include "PreCompileHeader.h"
#include "ModelCreator.h"
#include "../ModelStructure/ModelData/ModelDataAggregate.h"

//ツール
#include "ModelDataLoader/ModelDataLoader.h"

namespace
{
	auto const fileName = "ModelCreator.cpp";
}


MeshContext::ModelCreator::ModelCreator(MeshContext::InstanceKey key_)
{
	Logger::Entry("ModelCreator: Constructor");

    modelDataLoader.reset(new ModelDataLoader(key_));
    Logger::Log("Instantiate: ModelDataLoader", fileName);

    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();

	Logger::End("ModelCreator: Constructor");
}

MeshContext::ModelCreator::~ModelCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string , ModelDataAggregate*> MeshContext::ModelCreator::LoadAllModelFiles()
{
    std::string const registryFilePath = "Assets/Registry/ModelFiles.txt";

    std::unordered_map<std::string, ModelDataAggregate*> modelDataLib;

    auto modelFileName_pathLib = LoadModelRegistry(registryFilePath);

    for (const auto& [key, value] : modelFileName_pathLib)
    {
        //チェック
        ErrorMessageOutput::Assert::DetectError
        (
            modelFileName_pathLib.contains(key),
            key + "こんなファイルは存在しないぜ",
            fileName
        );

        modelDataLib[key] = modelDataLoader->Load(key, value);
    }

    return modelDataLib;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string, std::string > MeshContext::ModelCreator::LoadModelRegistry(std::string const registryFilePath_)
{
    std::unordered_map<std::string, std::string > modelFileName_pathLib;
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


        modelFileName_pathLib.emplace(key, value);
    }

    Logger::Log("Load: " + registryFilePath_, fileName);
    return modelFileName_pathLib;

}
