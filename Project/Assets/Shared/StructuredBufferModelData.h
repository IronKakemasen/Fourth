#pragma once

#ifdef __cplusplus

#include "../../Engine/MiddleLayer/Math/Vector/Vector2.h"
#include "../../Engine/MiddleLayer/Math/Vector/Vector3.h"
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"
#include "../../Engine/MiddleLayer/Math/Matrix/Matrix4x4.h"

namespace StructuredBufferModelData
{
    struct StandardVertexGPU
    {
        Vector4<float> localPos;
        Vector4<float> normal;
        Vector4<float> tangent;
        Vector4<float> texcoord;
    };

    struct StandardVertexCPU
    {
        StandardVertexCPU() {};

        StandardVertexCPU
        (
            Vector3 localPos_,
            Vector3 normal_,
            Vector3 tangent_,
            Vector2 texcoord_
        ) :localPos(localPos_), normal(normal_), tangent(tangent_), texcoord(texcoord_) {}

        Vector3 localPos;
        Vector3 normal;
        Vector3 tangent;
        Vector2 texcoord;
    };

    struct MaterialCPU
    {
        std::string albedoTexture;
        std::string normalTexture;
        std::string emissiveTexture;
        Vector4<float> baseColor;
        float roughness{};
        float metallic{};
    };

    struct MaterialGPU
    {
        SRVHeapIndex albedoTexture;
        SRVHeapIndex normalTexture;
        SRVHeapIndex emissiveTexture;
        Vector4<float> baseColor;
        float roughness{};
        float metallic{};
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

    struct MeshCPU
    {
        std::vector<StandardVertexCPU> vertices;
        std::vector<UniqueVertexIndexCPUGPU> uniqueVertexIndices;
        std::vector<MeshletCPUGPU> meshlets;
        std::vector<PrimitiveIndexCPUGPU> primitiveIndices;
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

struct Material
{
    uint albedoIndex;
    uint normalIndex;
    uint emissiveIndex;
    float4 baseColor;
    float roughness;
    float metallic;
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