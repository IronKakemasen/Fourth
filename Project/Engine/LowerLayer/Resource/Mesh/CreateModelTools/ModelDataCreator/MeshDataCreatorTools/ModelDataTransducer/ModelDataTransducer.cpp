#include "PreCompileHeader.h"
#include "ModelDataTransducer.h"

//外部
#include "../../../../../Buffer/RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"

using namespace StructuredBufferDataDefinition;

[[nodiscard]] std::vector<MeshContext::ModelDataCreator::MeshDataStructuredBufferGroup>
MeshContext::ModelDataCreator::DataTransducer::BufferUniqueID_To_BufferPtr
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
        meshDataStructuredBufferGroup.verticesGPUSTB =          tmpPtrGetterFunc((*itr).verticesGPUID);
        meshDataStructuredBufferGroup.uniqueVertsIndicesSTB =   tmpPtrGetterFunc((*itr).uniqueVertsIndicesID);
        meshDataStructuredBufferGroup.meshletsSTB =             tmpPtrGetterFunc((*itr).meshletsID);
        meshDataStructuredBufferGroup.primIndicesSTB =          tmpPtrGetterFunc((*itr).primIndicesID);

        meshDataStructuredBufferGroupContainer.emplace_back(meshDataStructuredBufferGroup);
    }

    return meshDataStructuredBufferGroupContainer;
}

std::vector<StandardVertexGPU> MeshContext::ModelDataCreator::DataTransducer::TransferVertexDataTypeToGPU(const std::vector<StandardVertex>& vertices_)
{
    std::vector<StandardVertexGPU> standardVertexGPUContainer;

    size_t const verticesSize = vertices_.size();
    standardVertexGPUContainer.resize(verticesSize);

    auto transferToVector4Func = [](float* data_, uint8_t size_ = 3)
        {
            Vector4<float> transferDst;

            for (uint8_t i = 0;i < size_;++i)
            {
                (&transferDst.x)[i] = data_[i];
            }

            return transferDst;
        };

    for (size_t i = 0;i < verticesSize;++i)
    {
        standardVertexGPUContainer[i].localPos =
            transferToVector4Func((float*)&vertices_[i].localPos.data.x);

        standardVertexGPUContainer[i].normal =
            transferToVector4Func((float*)&vertices_[i].normal.data.x);

        standardVertexGPUContainer[i].tangent =
            transferToVector4Func((float*)&vertices_[i].tangent.data.x);

        standardVertexGPUContainer[i].texcoord =
            transferToVector4Func((float*)&vertices_[i].texcoord.x, 2);
    }

    return standardVertexGPUContainer;
}