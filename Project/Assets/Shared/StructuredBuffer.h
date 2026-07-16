#pragma once
#include "../../Engine/Math/Vector/Vector4.h"
#include "../../Engine/Math/Matrix/Matrix4x4.h"

#ifdef __cplusplus

namespace StructuredBufferDataDefinition
{
    //標準的な頂点情報
    struct StandardVertexGPU
    {
        Vector4<float> localPos;
        Vector4<float> normal;
        Vector4<float> tangent;
        Vector4<float> texcoord;
    };

    struct MeshletCPUGPU
    {
        //頂点番号オフセット
        uint32_t vertexOffset;
        //頂点カウント
        uint32_t vertexCnt;
        //プリミティブ番号オフセット
        uint32_t primitiveOffset;
        //プリミティブカウント
        uint32_t primitiveCnt;
    };

    struct PrimitiveIndexCPUGPU
    {
        uint32_t index0     : 10;
        uint32_t index1     : 10;
        uint32_t index2     : 10;
        uint32_t reserved   : 2;
    };

    struct UniqueVertexIndexCPUGPU
    {
        UniqueVertexIndexCPUGPU(uint32_t index_)
        : index(index_) {}

        uint32_t index{};

    };

    struct TransformMatrixCPUGPU
    {
        Matrix4x4 wvp;
        Matrix4x4 world;
    };

    ///メッシュデータのバッファのSRVHeapIndexをひとまとまりにしたもの
    struct MeshDataSRVHeapIndexGroupGPU
    {
        SRVHeapIndex vertices{};
        SRVHeapIndex uniqueVertexIndices{};
        SRVHeapIndex meshlets{};
        SRVHeapIndex primitiveIndices{};
        ///マテリアルも追加予定?
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
    //頂点番号オフセット
    uint vertexOffset;
    //頂点数
    uint vertexCnt;
    //プリミティブ番号オフセット
    uint primitiveOffset;
    //プリミティブオフセット
    uint primitiveCnt;
};

struct OriginalIndex
{
    uint index;
};

struct PrimitiveIndex
{
    uint packedPrimitiveIndex;
};

struct UniqueVertexIndex
{
    uint index;
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