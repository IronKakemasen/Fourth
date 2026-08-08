#include "PreCompileHeader.h"
#include "ModelDataCreator.h"

#include "../../ModelStructure/ModelData/ModelDataAggregate.h"

#include "../ModelDataLoader/ModelDataLoader.h"
#include "../ModelSlotAllocator/MeshDataIDLibrary/MeshDataIDLibrary.h"

#include "MeshDataCreatorTools/ModelDataTransducer/ModelDataTransducer.h"
#include "MeshDataCreatorTools/MeshDataBufferCreator/MeshDataBufferCreator.h"
#include "MeshDataCreatorTools/MeshDataBufferUploader/MeshDataBufferUploader.h"
#include "MeshDataCreatorTools/MeshDataBufferSRVHeapIndexGroupPackager/MeshDataBufferSRVHeapIndexGroupPackager.h"
#include "MeshDataCreatorTools/MeshDataSRVHeapIndexGroupContainerBufferCreator/MeshDataSRVHeapIndexGroupContainerBufferCreator.h"
#include "MeshDataCreatorTools/TransformMatrixContainerBufferCreator/TransformMatrixContainerBufferCreator.h"

//外部
#include "../../../Buffer/BufferContextDiplomat/BufferDiplomatIncludes.h"

#include "RegistryLoader/RegistryLoader.h"

using namespace StructuredBufferDataDefinition;

namespace
{
	auto const fileName = "ModelDataCreator.cpp";
}


ModelContext::ModelDataCreator::ModelDataCreator
(
    NexusFieldProof proof_,
    std::unique_ptr<ModelDataLoader>&& modelDataLoader_,
    ModelSlotAllocator* allocator_,
    ModelDataBatcher* modelDataBatcher_,
    BufferContextDiplomat* bufferContextDiplomat_
) :modelDataLoader(std::move(modelDataLoader_))
{
	Logger::Entry("ModelDataCreator: Constructor");

    CreateAllModelData(proof_, allocator_, modelDataBatcher_,bufferContextDiplomat_);

	Logger::End("ModelDataCreator: Constructor");
}

ModelContext::ModelDataCreator::~ModelDataCreator()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModelContext::ModelDataCreator::CreateAllModelData
(
    NexusFieldProof proof_,
    ModelContext::ModelSlotAllocator* allocator_,
    ModelDataBatcher* modelDataBatcher_,
    BufferContextDiplomat* bufferContextDiplomat_
)
{
    ///＜目標＞
    ///0.全てのメッシュデータのスタティックストラクチャードバッファを生成して、バッファアップローダーに
    ///登録する
    ///1.そのキー(ファイル名)に対してメッシュデータバッファのsrvHeapIndex群のID(マルチメッシュ対応のためvector)
    ///を紐づける。後にこの値は各モデルがRootConstantsでGPUに転送する
    ///2.メッシュデータバッファのsrvHeapIndex群のコンテナを1つのストラクチャードバッファとして生成して
    ///アップロードし、MeshSlotAllocatorがそのバッファのsrvHeapIndexを保存する
    ///3.TransformMatrixContainerのuploadStructuredBufferを作成。そのsrvHeapIndexの
    ///ワールド定数バッファを作成し、データを入力


    ///メッシュデータ生成数
    ///メッシュIDが指す先は一つのメッシュデータバッファのsrvheapIndex群であり、
    ///マルチメッシュで3つ存在していた場合、IDが3つできることを意味する
    MeshDataID meshDataID{};

    ///メッシュデータのsrvHeapIndexがひとまとまりになったものの一時コンテナ
    ///全てのメッシュデータ分を詰めていき、最後にstaticStruturedBufferを作成しマッピング。アップロードする
    ///そのバッファのsrvHeapIndexは配列に詰められ、コンスタントバッファとして転送される。
    std::vector<MeshDataSRVHeapIndexGroupGPUCPU> tmpMeshDataSRVHeapIndexGroupContainer;


    //モデルデータライブラリー
    std::unordered_map<std::string, ModelDataAggregate*> tmpModelDataLib = LoadAllModelFiles();

    //バッファコンテキストのツールレンダーから各種ツールを借りる
    auto [bufferCreator, bufferCollector, bufferUploader,bufferDispatcher] =
        BorrowBufferContextTools(bufferContextDiplomat_);

    //定数バッファ生成コマンドを提供してもらう
    BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licence;
    auto createCBufferCmd = bufferContextDiplomat_->Access<BufferContext::CmdProvider>()->
        Provide<BufferContextCmds::CreateCBufferCmd>(licence);


    for (const auto& [key, value] : tmpModelDataLib)
    {
        //メッシュデータのバッファを生成する
        std::vector<MeshDataBufferUniqueIDGroup> meshDataBufferUniqueIDGroupContainer =
        MeshDataBufferCreator::CreateMeshDataBuffer
        (
            allocator_,
            value->resourceMesh, 
            bufferCreator, 
            bufferCollector, 
            key, 
            meshDataID
        );

        //BufferUploaderが
        //メッシュデータバッファのユニークIDをもとに実メッシュデータをマッピングして、アップロードする
        MeshDataBufferUploader::CopyAndUploadBuffer
        (
            value->resourceMesh,
            meshDataBufferUniqueIDGroupContainer,
            bufferUploader
        );

        //メッシュデータのユニークIDをもとにそれぞれのsrvHeapIndexを引き出し、
        //tmpMeshDataSRVHeapIndexGroupContainer
        //こいつに詰めていく。こいつのインデックスはmeshDataIDとリンクしている
        MeshDataBufferSRVHeapIndexGroupPackager::PackMeshDataBufferSRVHeapIndex
        (
            meshDataBufferUniqueIDGroupContainer,
            tmpMeshDataSRVHeapIndexGroupContainer,
            bufferDispatcher
        );
    }

    ///tmpMeshDataSRVHeapIndexGroupContainerのバッファを作る
    ///そのsrvHeapIndexの定数バッファも作成する
    MeshDataSRVHeapIndexGroupContainerBufferCreator::Create
    (
        tmpMeshDataSRVHeapIndexGroupContainer,
        bufferCreator,
        bufferUploader,
        createCBufferCmd
    );


    ///TransformMatrixのコンテナのUploadStructuredBufferを作成し、
    ///そのsrvHeapIndexの定数バッファも作成する。
    ///ランタイム用にTransformMatrixのコンテナのバッファのユニークIDをmodelDataBatcherが保管する
    TransformMatrixContainerBufferCreator::Create
    (
        bufferCreator,
        createCBufferCmd,
        modelDataBatcher_

    );

    //meshDataIDLibraryの中身をログ出力
    auto& meshDataIDLibrary = allocator_->AccessMeshDataIDLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
    meshDataIDLibrary.Log();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string , ModelDataAggregate*> ModelContext::ModelDataCreator::LoadAllModelFiles()
{
    std::unordered_map<std::string, ModelDataAggregate*> modelDataLib;

    auto modelFileName_pathLib = RegistryLoader::Load<RegistryLoader::RegistryFileType::kModelFiles>();

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
ModelContext::ModelDataCreator::BufferContextTools ModelContext::ModelDataCreator::BorrowBufferContextTools(BufferContextDiplomat* bufferContextDiplomat_)
{
    //バッファコンテキストのツールレンダーからいろんなツールを借りる
    auto bufferToolLender = bufferContextDiplomat_->Access<BufferContext::ToolLender>();
    BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
    
    auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);
    auto* bufferCollector = bufferToolLender->Lend<BufferContext::BufferCollector>(licence);
    auto* bufferUploader = bufferToolLender->Lend<BufferContext::BufferUploader>(licence);
    auto* bufferDispatcher = bufferToolLender->Lend<BufferContext::BufferDispatcher>(licence);

    return std::make_tuple(bufferCreator, bufferCollector, bufferUploader, bufferDispatcher);
}
