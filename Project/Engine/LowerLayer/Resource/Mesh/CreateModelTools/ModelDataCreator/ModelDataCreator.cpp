#include "PreCompileHeader.h"
#include "ModelDataCreator.h"
#include "../ModelSlotAllocator/ModelSlotAllocator.h"
#include "../../ModelStructure/ModelData/ModelDataAggregate.h"

#include "MeshDataCreatorTools/ModelDataTransducer/ModelDataTransducer.h"
#include "MeshDataCreatorTools/MeshDataBufferCreator/MeshDataBufferCreator.h"
#include "../ModelDataLoader/ModelDataLoader.h"
#include "MeshDataCreatorTools/ModelRegistryLoader/ModelRegistryLoader.h"

//外部
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"



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
    MeshDataID meshDataID{};

    ///メッシュデータのsrvHeapIndexがひとまとまりになったものの一時コンテナ
    ///全てのメッシュデータ分を詰めていき、最後にstaticStruturedBufferを作成しマッピング。アップロードする
    ///そのバッファのsrvHeapIndexは配列に詰められ、コンスタントバッファとして転送される。
    std::vector<MeshDataSRVHeapIndexGroupGPUCPU> tmpMeshDataSRVHeapIndexGroupContainer;


    //メッシュデータのバッファを作る


    //モデルデータライブラリー
    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();

    //バッファコンテキストのツールレンダーから各種ツールを借りる
    auto [bufferCreator, bufferCollector, bufferDispatcher, bufferUploader] =
        BorrowBufferContextTools(bufferContextDiplomat_);

    for (const auto& [key, value] : tmpModelDataLib)
    {
        //メッシュデータのバッファを生成する
        std::vector<MeshDataBufferUniqueIDGroup> meshDataBufferUniqueIDGroupContainer =
        MeshDataBufferCreator::CreateMeshDataBuffer
        (
            meshDataIDLib,
            value->resourceMesh, 
            bufferCreator, 
            bufferCollector, 
            key, 
            meshDataID
        );

        //生成したメッシュデータバッファのユニークID群からバッファのポインタを探す
        std::vector<MeshDataStructuredBufferGroup> MeshDataStructuredBufferGroupContainer =
            DataTransducer::BufferUniqueID_To_BufferPtr(meshDataBufferUniqueIDGroupContainer, bufferDispatcher);

        //BufferUploaderが
        //静的バッファのポインタをもとに実メッシュデータをマッピングして、アップロードする


    }

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string , ModelDataAggregate*> MeshContext::ModelDataCreator::LoadAllModelFiles()
{
    std::unordered_map<std::string, ModelDataAggregate*> modelDataLib;

    auto modelFileName_pathLib = ModelRegistryLoader::Load();

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
