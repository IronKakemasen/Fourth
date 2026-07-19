#include "PreCompileHeader.h"
#include "ModelDataCreator.h"
#include "../../ModelStructure/ModelData/ModelDataAggregate.h"

//ツール
#include "ModelDataLoader/ModelDataLoader.h"
#include "../ModelSlotAllocator/ModelSlotAllocator.h"
#include "../../../Buffer/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../../Buffer/BufferCreateTools/BufferCreator.h"

namespace
{
	auto const fileName = "ModelDataCreator.cpp";
}


MeshContext::ModelDataCreator::ModelDataCreator(MeshContext::InstanceKey key_, BufferContext* bufferContext_)
{
	Logger::Entry("ModelDataCreator: Constructor");

    modelDataLoader.reset(new ModelDataLoader(key_));
    Logger::Log("Instantiate: ModelDataLoader", fileName);

    BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};

    auto* bufferCreator = bufferContext_->toolLender->Lend<BufferContext::BufferCreator>(licence);
    auto* bufferUploader = bufferContext_->toolLender->Lend<BufferContext::BufferUploader>(licence);
    

	Logger::End("ModelDataCreator: Constructor");
}

MeshContext::ModelDataCreator::~ModelDataCreator()
{

}


void MeshContext::ModelDataCreator::CreateAllModelData(MeshContext::ModelSlotAllocator* allocator_)
{
    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();


    ///メッシュIDとファイル名を紐づける
    UINT meshID{};
    {
        for (const auto& [key, value] : tmpModelDataLib)
        {
            meshDataIDLib[key] = MeshDetaID(meshID++);
        }
    }

    //モデルの種類の数
    UINT numModelTypes = meshID + 1;
}

void MeshContext::ModelDataCreator::CreateMeshDataBuffer(const ResourceMesh& data_)
{
    //data_.meshlets
}


///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string , ModelDataAggregate*> MeshContext::ModelDataCreator::LoadAllModelFiles()
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
std::unordered_map<std::string, std::string > MeshContext::ModelDataCreator::LoadModelRegistry(std::string const registryFilePath_)
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
