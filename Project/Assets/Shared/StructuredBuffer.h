#pragma once

#ifdef __cplusplus

#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"
#include "../../Engine/MiddleLayer/Math/Matrix/Matrix4x4.h"

namespace StructuredBufferDataDefinition
{
    struct StandardVertexGPU
    {
        Vector4<float> localPos;
        Vector4<float> normal;
        Vector4<float> tangent;
        Vector4<float> texcoord;
    };

    struct MeshletCPUGPU
    {
        uint32_t vertexOffset;
        uint32_t vertexCnt;
        uint32_t primitiveOffset;
        uint32_t primitiveCnt;
    };

    struct PrimitiveIndexCPUGPU
    {
        uint32_t index0 : 10;
        uint32_t index1 : 10;
        uint32_t index2 : 10;
        uint32_t reserved : 2;
    };

    struct UniqueVertexIndexCPUGPU
    {
        UniqueVertexIndexCPUGPU(uint32_t index_)
            : index(index_) {
        }

        uint32_t index{};

    };

    struct TransformMatrixCPUGPU
    {
        Matrix4x4 wvp;
        Matrix4x4 world;
    };

    struct MeshDataSRVHeapIndexGroupGPUCPU
    {
        SRVHeapIndex vertices{};
        SRVHeapIndex uniqueVertexIndices{};
        SRVHeapIndex meshlets{};
        SRVHeapIndex primitiveIndices{};
    };
}

#else

struct StandardVertex
{
    float4 localPos;
    float4 normal;
    float4 tangent;
    float4 texcoord;
};

struct Meshlet
{
    uint vertexOffset;
    uint vertexCnt;
    uint primitiveOffset;
    uint primitiveCnt;
};

struct TransformMatrix
{
    float4x4 wvp;
    float4x4 world;
};

struct MeshDataSRVHeapIndexGroup
{
    uint vertices;
    uint uniqueVertexIndices;
    uint meshlets;
    uint primitiveIndices;

};

#endif