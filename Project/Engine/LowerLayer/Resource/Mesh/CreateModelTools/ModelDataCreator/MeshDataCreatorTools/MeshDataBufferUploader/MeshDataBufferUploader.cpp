#include "PreCompileHeader.h"
#include "MeshDataBufferUploader.h"
#include "../ModelDataTransducer/ModelDataTransducer.h"


//外部
#include "../../../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"

namespace
{
    auto const fileName = "MeshDataBufferUploader.cpp";
}

using namespace StructuredBufferDataDefinition;

void MeshContext::ModelDataCreator::MeshDataBufferUploader::CopyAndUploadBuffer
(
	const std::vector<ResourceMesh>& data_,
    const std::vector<MeshDataBufferUniqueIDGroup>& meshDataBufferUniqueIDGroupContainer_,
    BufferContext::BufferUploader* bufferUploader_
)
{
    size_t numMeshData = data_.size();
    ErrorMessageOutput::Assert::DetectError
    (
        numMeshData == meshDataBufferUniqueIDGroupContainer_.size(),
        "メッシュデータとmeshDataBufferUniqueIDGroupの比が合わない",
        fileName
    );

    //CPUにマッピングしてアップロードする
    for (size_t i = 0;i < numMeshData;++i)
    {

        //頂点データをGPU仕様にする
        std::vector<StandardVertexGPU> vertexGPU =
            MeshContext::ModelDataCreator::DataTransducer::TransferVertexDataTypeToGPU(data_[i].vertices);

        //頂点データ
        bufferUploader_->UploadBuffer
        (
            meshDataBufferUniqueIDGroupContainer_[i].verticesGPUID,
            (UINT)vertexGPU.size(),
            vertexGPU.data()
        );

        //頂点インデックス
        bufferUploader_->UploadBuffer
        (
            meshDataBufferUniqueIDGroupContainer_[i].uniqueVertsIndicesID,
            (UINT)data_[i].uniqueVertexIndices.size(),
            data_[i].uniqueVertexIndices.data()
        );

        //メッシュレット
        bufferUploader_->UploadBuffer
        (
            meshDataBufferUniqueIDGroupContainer_[i].meshletsID,
            (UINT)data_[i].meshlets.size(),
            data_[i].meshlets.data()
        );

        //三角形頂点構成番号
        bufferUploader_->UploadBuffer
        (
            meshDataBufferUniqueIDGroupContainer_[i].primIndicesID,
            (UINT)data_[i].primitiveIndices.size(),
            data_[i].primitiveIndices.data()
        );

    }

}
