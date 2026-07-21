#include "PreCompileHeader.h"
#include "ModelDataCreator.h"
#include "ModelDataLoader/ModelDataLoader.h"
#include "../ModelSlotAllocator/ModelSlotAllocator.h"
#include "../../ModelStructure/ModelData/ModelDataAggregate.h"

//外部
#include "../../../Buffer/BufferDefinition/BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../../Buffer/RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"
#include "../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../../../Assets/Shared/StructuredBuffer.h"



using namespace StructuredBufferDataDefinition;

namespace
{
	auto const fileName = "ModelDataCreator.cpp";
}


MeshContext::ModelDataCreator::ModelDataCreator
(
    MeshContext::InstanceKey key_,
    MeshContext::ModelSlotAllocator* allocator_,
    BufferContextDiplomat* bufferContextDiplomat_
)
{
	Logger::Entry("ModelDataCreator: Constructor");

    modelDataLoader.reset(new ModelDataLoader(key_));
    Logger::Log("Instantiate: ModelDataLoader", fileName);

    CreateAllModelData(allocator_, bufferContextDiplomat_);

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
    BufferContextDiplomat* bufferContextDiplomat_
)
{
    ///＜最終目的＞
    ///そのキー(ファイル名)に対してメッシュデータID(マルチメッシュ対応のためvector)を紐づける。

    ///メッシュデータ生成数
    ///メッシュIDが指す先は一つのメッシュデータバッファのsrvheapIndex群であり、
    ///マルチメッシュで3つ存在していた場合、IDが3つできることを意味する
    MeshDetaID meshDataID{};

    ///メッシュデータのsrvHeapIndexがひとまとまりになったものの一時コンテナ
    ///全てのメッシュデータ分を詰めていき、最後にstaticStruturedBufferを作成しマッピング。アップロードする
    ///そのバッファのsrvHeapIndexは配列に詰められ、コンスタントバッファとして転送される。
    std::vector<MeshDataSRVHeapIndexGroupGPUCPU> tmpMeshDataSRVHeapIndexGroupContainer;


    //モデルデータライブラリー
    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();

    //バッファコンテキストのツールレンダーから各種ツールを借りる
    auto [bufferCreator, bufferCollector, bufferDispatcher, bufferUploader] =
        BorrowBufferContextTools(bufferContextDiplomat_);


    for (const auto& [key, value] : tmpModelDataLib)
    {
        //メッシュデータのバッファを生成する
        std::vector<MeshDataBufferUniqueIDGroup> meshDataBufferUniqueIDGroupContainer =
            CreateMeshDataBuffer(value->resourceMesh, bufferCreator, bufferCollector, key, meshDataID);

        //生成したメッシュデータバッファのユニークID群からバッファのポインタを探す
        std::vector<MeshDataStructuredBufferGroup> MeshDataStructuredBufferGroupContainer =
            BufferUniqueID_To_BufferPtr(meshDataBufferUniqueIDGroupContainer, bufferDispatcher);


        //生成されたバッファユニークID群をもとにバッファのポインタを取得し、アップロードする


    }

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<MeshContext::ModelDataCreator::MeshDataBufferUniqueIDGroup> MeshContext::ModelDataCreator::CreateMeshDataBuffer
(
    const std::vector<ResourceMesh>& data_,
    BufferContext::BufferCreator* bufferCreator_,
    BufferContext::BufferCollector* bufferCollector_,
    std::string meshDataName_,
    MeshDetaID& meshDataID_
)
{
    ///メッシュデータのバッファユニークID群のコンテナ
    std::vector<MeshDataBufferUniqueIDGroup> meshDataBufferUniqueIDContainer;

    //バッファディスクを作り、それをもとにバッファを生成してユニークIDを返す
    auto tmpCreateBufferFunc = [bufferCreator_]<typename DataType>(size_t size_,std::string meshDataKey_, std::string bufferName_)
    {
        std::string bufferName = meshDataKey_ + "<" + bufferName_ + ">";
        StaticStructuredBufferDescription desc(sizeof(DataType), (UINT)size_, 0);

        return bufferCreator_->Create(desc, bufferName);
    };

    ///メッシュデータのGPUバッファを作成
    for (const auto& meshData : data_)
    {
        MeshDataBufferUniqueIDGroup meshDataBufferUniqueID;

        //マルチメッシュに対応するために、インデックスの文字列をキーに含める
        std::string meshDataKey = meshDataName_ + std::to_string((UINT)meshDataID_);
        meshDataIDLib[meshDataKey] = MeshDetaID(meshDataID_++);

        //ディスクをもとにバッファを生成
        meshDataBufferUniqueID.verticesID           = tmpCreateBufferFunc.operator()<StandardVertexGPU>(meshData.vertices.size(), meshDataKey,"Vertices");
        meshDataBufferUniqueID.uniqueVertsIndicesID = tmpCreateBufferFunc.operator()<UniqueVertexIndexCPUGPU>(meshData.uniqueVertexIndices.size(), meshDataKey, "UniqueVertsIndices");
        meshDataBufferUniqueID.meshletsID           = tmpCreateBufferFunc.operator()<MeshletCPUGPU>(meshData.meshlets.size(), meshDataKey, "Meshlets");
        meshDataBufferUniqueID.primIndicesID        = tmpCreateBufferFunc.operator()<PrimitiveIndexCPUGPU>(meshData.primitiveIndices.size(), meshDataKey,"PrimIndices");

        meshDataBufferUniqueIDContainer.emplace_back(meshDataBufferUniqueID);
    }

    //バッファコレクターに生成したバッファを仕分けしてもらう
    bufferCollector_->Distribute();

    //メッシュデータのバッファユニークID群を返す
    return meshDataBufferUniqueIDContainer;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<MeshContext::ModelDataCreator::MeshDataStructuredBufferGroup> 
MeshContext::ModelDataCreator::BufferUniqueID_To_BufferPtr
(
    const std::vector<MeshDataBufferUniqueIDGroup>& uniqueIDGroup_,
    BufferContext::BufferDispatcher* bufferDispatcher_
) 
{
    //メッシュデータのバッファのポインタ群のコンテナ
    std::vector<MeshDataStructuredBufferGroup> meshDataStructuredBufferGroupContainer;

    auto tmpPtrGetterFunc = [bufferDispatcher_](BufferUniqueID id_)
    {
        return static_cast<StaticStructuredBuffer*>(bufferDispatcher_->Dispatch(id_));
    };

    for (auto itr = uniqueIDGroup_.begin();itr != uniqueIDGroup_.end();++itr)
    {
        MeshDataStructuredBufferGroup meshDataStructuredBufferGroup;
     
        //メッシュデータごとにアドレスを取得して詰めていく
        meshDataStructuredBufferGroup.verticesSTB           = tmpPtrGetterFunc((*itr).verticesID);
        meshDataStructuredBufferGroup.uniqueVertsIndicesSTB = tmpPtrGetterFunc((*itr).verticesID);
        meshDataStructuredBufferGroup.meshletsSTB           = tmpPtrGetterFunc((*itr).verticesID);
        meshDataStructuredBufferGroup.primIndicesSTB        = tmpPtrGetterFunc((*itr).verticesID);

        meshDataStructuredBufferGroupContainer.emplace_back(meshDataStructuredBufferGroup);
    }

    return meshDataStructuredBufferGroupContainer;
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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshContext::ModelDataCreator::BufferContextTools MeshContext::ModelDataCreator::BorrowBufferContextTools(BufferContextDiplomat* bufferContextDiplomat_)
{
    //バッファコンテキストのツールレンダーから、
    //bufferCreator、bufferDispatcher、bufferCollector、uploaderを借りる
    auto bufferToolLender = bufferContextDiplomat_->Access<BufferContext::ToolLender>();
    BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
    auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);
    auto* bufferCollector = bufferToolLender->Lend<BufferContext::BufferCollector>(licence);
    auto* bufferDispatcher = bufferToolLender->Lend<BufferContext::BufferDispatcher>(licence);
    auto* bufferUploader = bufferToolLender->Lend<BufferContext::BufferUploader>(licence);

    return std::make_tuple(bufferCreator, bufferCollector, bufferDispatcher, bufferUploader);
}
