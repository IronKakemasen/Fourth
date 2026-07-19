#include "PreCompileHeader.h"
#include "ModelDataCreator.h"
#include "../../ModelStructure/ModelData/ModelDataAggregate.h"

#include "../../../../../../Assets/Shared/StructuredBuffer.h"
#include "../../../Buffer/BufferDefinition/BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"

//ツール
#include "ModelDataLoader/ModelDataLoader.h"
#include "../ModelSlotAllocator/ModelSlotAllocator.h"
#include "../../../Buffer/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../../Buffer/BufferCreateTools/BufferCreator.h"


using namespace StructuredBufferDataDefinition;

namespace
{
	auto const fileName = "ModelDataCreator.cpp";
}


MeshContext::ModelDataCreator::ModelDataCreator
(
    MeshContext::InstanceKey key_,
    MeshContext::ModelSlotAllocator* allocator_,
    BufferContext* bufferContext_
)
{
	Logger::Entry("ModelDataCreator: Constructor");

    modelDataLoader.reset(new ModelDataLoader(key_));
    Logger::Log("Instantiate: ModelDataLoader", fileName);

    CreateAllModelData(allocator_, bufferContext_);

	Logger::End("ModelDataCreator: Constructor");
}

MeshContext::ModelDataCreator::~ModelDataCreator()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshContext::ModelDataCreator::CreateAllModelData
(
    MeshContext::ModelSlotAllocator* allocator_,
    BufferContext* bufferContext_
)
{
    //モデルデータライブラリー
    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();

    //bufferCreatorとuploaderを借りる
    BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
    auto* bufferCreator = bufferContext_->toolLender->Lend<BufferContext::BufferCreator>(licence);
    auto* bufferUploader = bufferContext_->toolLender->Lend<BufferContext::BufferUploader>(licence);

    ///メッシュIDとファイル名を紐づける
    for (const auto& [key, value] : tmpModelDataLib)
    {
        //メッシュデータのバッファを生成する
        CreateMeshDataBuffer(value->resourceMesh, allocator_, bufferCreator, key);
    }

    //モデルの種類の数
    //UINT numModelTypes = meshID + 1;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshContext::ModelDataCreator::CreateMeshDataBuffer
(
    const std::vector<ResourceMesh>& data_,
    MeshContext::ModelSlotAllocator* allocator_,
    BufferContext::BufferCreator* bufferCreator_,
    std::string meshDataName_
)
{
    UINT meshID{};

    ///メッシュデータのGPUバッファを作成
    for (const auto& meshData : data_)
    {
        //マルチメッシュに対応するために、インデックスの文字列をキーに含める
        std::string meshDataKey = meshDataName_ + std::to_string(meshID);
        meshDataIDLib[meshDataKey] = MeshDetaID(meshID++);

        //まずはディスクの定義から
        StaticStructuredBufferDescription descVertices(sizeof(StandardVertexGPU), (UINT)meshData.vertices.size(), 0);
        StaticStructuredBufferDescription descUniqueVertsIndices(sizeof(UniqueVertexIndexCPUGPU), (UINT)meshData.uniqueVertexIndices.size(), 0);
        StaticStructuredBufferDescription descMeshlets(sizeof(MeshletCPUGPU), (UINT)meshData.meshlets.size(), 0);
        StaticStructuredBufferDescription descPrimIndices(sizeof(PrimitiveIndexCPUGPU), (UINT)meshData.primitiveIndices.size(), 0);

        //ディスクをもとにバッファを生成
        BufferUniqueID tmp_idVertices = bufferCreator_->Create(descVertices, meshDataKey + "[Vertices]");
        BufferUniqueID tmp_idUniqueVertsIndices = bufferCreator_->Create(descUniqueVertsIndices, meshDataKey + "[UniqueVertsIndices]");
        BufferUniqueID tmp_idMeshlets = bufferCreator_->Create(descMeshlets, meshDataKey + "[Meshlets]");
        BufferUniqueID tmp_idPrimIndices = bufferCreator_->Create(descPrimIndices, meshDataKey + "[PrimIndices ]");

    }

    

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
