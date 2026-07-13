#pragma once
#include "../../Engine/Math/Vector/Vector4.h"
#include "../../Engine/Math/Matrix/Matrix4x4.h"

#ifdef __cplusplus

//標準的な頂点情報
struct StandardVertex
{
    Vector4<float> localPos;
    Vector4<float> normal;
    Vector4<float> tangent;
    Vector4<float> texcoord;
};

//インデックスの原本
struct OriginalIndex
{
    uint32_t index;
};

struct Meshlet
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

struct PrimitiveIndex 
{
    uint32_t index0   : 10;
    uint32_t index1   : 10;
    uint32_t index2   : 10;
    uint32_t reserved : 2;
};

struct UniqueVertexIndex
{
    uint32_t index;
};

struct TransformMatrix
{
    Matrix4x4 wvp;
    Matrix4x4 world;
};



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

#endif