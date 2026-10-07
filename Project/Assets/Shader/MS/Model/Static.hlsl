#include "../../../Shared/StructuredBufferModelData.h"
#include "../../../Shared/StructuredBufferCameraData.h"
#include "../../../Shared/ConstantBuffers.h"

#include "HLSLI/ModelDrawCommon.hlsli"


//そのモデルを構築するまでに利用するwvp
//groupThreadIDの0番が代表して更新する
groupshared float4x4 groupSharedWvp;

[numthreads(64, 1, 1)]
[outputtopology("triangle")]
void main
(
    uint groupThreadID_ : SV_GroupThreadID,
    uint groupID_ : SV_GroupID,
    out vertices MS_StandardOutput verts_[64],
    out indices uint3 polys_[126]
)
{
    //トランスフォームマトリックスの実データ配列
    StructuredBuffer<TransformMatrix> transformMatrixContainer = ResourceDescriptorHeap[gTransformMatrixContainerIndex];
    //メッシュデータのSrvIndex群配列(2段階参照)
    StructuredBuffer<MeshDataSRVHeapIndexGroup> meshDataSRVContainer = ResourceDescriptorHeap[gMeshDataIndexContainer];
    //カメラの実データ配列
    StructuredBuffer<CameraData> cameraDataContainer = ResourceDescriptorHeap[gCameraContainerIndex];

    //トランスフォーム実データ配列から、モデルの指定するインデックスをもとに引っ張ってくる
    TransformMatrix thisTransformMatrix = transformMatrixContainer[gPerDrawIndices.transformMatrixID];
    //メッシュデータのSrvIndex群配列から個々のMeshDataIDをもとに該当のSrvIndex群を引っ張る
    MeshDataSRVHeapIndexGroup srcMeshDataSrvGroup = meshDataSRVContainer[gPerDrawIndices.meshDataID];
    //カメラの実データ配列からこのPassで使うものを指定する(数もどれかもPass依存)
    CameraData srcCameraData = cameraDataContainer[gPassConstants.cameraOffset];
    
    //引っ張ってきたSrvIndex群から、実データを引っ張る
    StructuredBuffer<StandardVertex> vertices = ResourceDescriptorHeap[srcMeshDataSrvGroup.vertices];
    StructuredBuffer<uint> uniqueIndices = ResourceDescriptorHeap[srcMeshDataSrvGroup.uniqueVertexIndices];
    StructuredBuffer<Meshlet> meshlets = ResourceDescriptorHeap[srcMeshDataSrvGroup.meshlets];
    StructuredBuffer<uint> primitiveIndices = ResourceDescriptorHeap[srcMeshDataSrvGroup.primitiveIndices];

    
    Meshlet meshlet = meshlets[groupID_];

    //スレッドグループの頂点数とポリゴン数を設定
    //全スレッドが同じ値で呼ぶことで、制御フロー上「必ず先に実行される」ことを保証する
    SetMeshOutputCounts(meshlet.vertexCnt, meshlet.primitiveCnt);

    if (groupThreadID_ == 0)
    {
        groupSharedWvp = mul(thisTransformMatrix.world, srcCameraData.viewProj);
    }
    
    GroupMemoryBarrierWithGroupSync();
    
    if (groupThreadID_ < meshlet.vertexCnt)
    {
        uint accessID_uniqueIndices = groupThreadID_ + meshlet.vertexOffset;
        uint vertexIndex = uniqueIndices[accessID_uniqueIndices];
        StandardVertex dst_vertex = vertices[vertexIndex];

        verts_[groupThreadID_].position = mul(dst_vertex.localPos, groupSharedWvp);
        verts_[groupThreadID_].normal = normalize(mul(dst_vertex.normal, thisTransformMatrix.world).xyz);
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