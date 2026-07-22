#include "PreCompileHeader.h"
#include "ModelDataTransducer.h"

//外部
#include "../../../../../Buffer/RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"

using namespace StructuredBufferDataDefinition;


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