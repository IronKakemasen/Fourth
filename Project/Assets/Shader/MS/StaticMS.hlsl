#include "../../Shared/StructuredBuffer.h"
#include "../../Shared/ConstantBuffers.h"

struct MSOutput
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITION0;

};

uint3 UnpackPrimitiveIndex(uint packedIndex_)
{
    //0x3ff = 0b1111111111
    //>>10 = 10bit右側にずらす
    return uint3
    (
        packedIndex_ & 0x3FF,
        (packedIndex_ >> 10) & 0x3FF,
        (packedIndex_ >> 20) & 0x3FF
    );
}





[numthreads(64, 1, 1)]
[outputtopology("triangle")]
void main
(
    uint groupThreadID_ : SV_GroupThreadID,
    uint groupID_ : SV_GroupID,
    out vertices MSOutput verts_[64],
    out indices uint3 polys_[126]
)
{
    StructuredBuffer<TransformMatrix> transformMatrixContainer = ResourceDescriptorHeap[gTransformMatrixContainerIndex];
    StructuredBuffer<MeshDataSRVHeapIndexGroup> meshDataSRVContainer = ResourceDescriptorHeap[gModelDataContainerIndex];

    
    TransformMatrix transformMatrix = transformMatrixContainer[gPerDrawIndices.transformMatrixID];
    MeshDataSRVHeapIndexGroup srcMeshDataSrvGroup = meshDataSRVContainer[gPerDrawIndices.modelDataID];

    StructuredBuffer<StandardVertex> vertices = ResourceDescriptorHeap[srcMeshDataSrvGroup.vertices];
    StructuredBuffer<uint> uniqueIndices = ResourceDescriptorHeap[srcMeshDataSrvGroup.uniqueVertexIndices];
    StructuredBuffer<Meshlet> meshlets = ResourceDescriptorHeap[srcMeshDataSrvGroup.meshlets];
    StructuredBuffer<uint> primitiveIndices = ResourceDescriptorHeap[srcMeshDataSrvGroup.primitiveIndices];

    
    Meshlet meshlet = meshlets[groupID_];

    //スレッドグループの頂点数とポリゴン数を設定
    //全スレッドが同じ値で呼ぶことで、制御フロー上「必ず先に実行される」ことを保証する
    SetMeshOutputCounts(meshlet.vertexCnt, meshlet.primitiveCnt);

    if (groupThreadID_ < meshlet.vertexCnt)
    {
        uint accessID_uniqueIndices = groupThreadID_ + meshlet.vertexOffset;
        uint vertexIndex = uniqueIndices[accessID_uniqueIndices];
        StandardVertex dst_vertex = vertices[vertexIndex];

        verts_[groupThreadID_].position = mul(dst_vertex.localPos, transformMatrix.wvp);
        verts_[groupThreadID_].normal = normalize(mul(dst_vertex.normal, transformMatrix.world).xyz);
        verts_[groupThreadID_].texcoord = dst_vertex.texcoord.xy;
        verts_[groupThreadID_].worldPosition = float3(1, 1, 1);

    }


    for (uint i = groupThreadID_; i < meshlet.primitiveCnt; i += 64)
    {
        uint accessID_primitiveIndices = meshlet.primitiveOffset + i;
        uint packedIndex = primitiveIndices[accessID_primitiveIndices];
        polys_[i] = UnpackPrimitiveIndex(packedIndex);
    }

}