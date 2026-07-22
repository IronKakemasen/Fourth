#include "PreCompileHeader.h"
#include "MeshDataBufferCreator.h"
#include "../../../../ModelStructure/ModelData/ResourceMesh/ResourceMesh.h"
#include "../../../ModelSlotAllocator/ModelSlotAllocator.h"


//外部
#include "../../../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"

using namespace StructuredBufferDataDefinition;

[[nodiscard]] std::vector<MeshContext::ModelDataCreator::MeshDataBufferUniqueIDGroup> 
MeshContext::ModelDataCreator::MeshDataBufferCreator::CreateMeshDataBuffer
(
    MeshContext::ModelSlotAllocator* allocator_, 
    const std::vector<ResourceMesh>& data_,
	BufferContext::BufferCreator* bufferCreator_,
	BufferContext::BufferCollector* bufferCollector_,
	std::string modelFileName_,
	MeshDataID& meshDataID_
)
{
    ///メッシュデータのバッファユニークID群のコンテナ
    std::vector<MeshDataBufferUniqueIDGroup> meshDataBufferUniqueIDContainer;

    //バッファディスクを作り、それをもとにバッファを生成してユニークIDを返す
    auto tmpCreateBufferFunc = [bufferCreator_]<typename DataType>(size_t size_, std::string meshDataKey_, std::string bufferName_)
    {
        std::string bufferName = meshDataKey_ + "<" + bufferName_ + ">";
        StaticStructuredBufferDescription desc(sizeof(DataType), (UINT)size_, 0);

        return bufferCreator_->Create(desc, bufferName);
    };

    //サブメッシュのカウント。バッファの命名に使用
    UINT subMeshCnt{};
    //MeshDataBufferUniqueIDGroupコンテナ上の番地を記録するため。(サブメッシュも含む)
    std::vector<MeshDataID> meshDataIDContainer;

    ///メッシュデータのGPUバッファを作成
    for (const auto& meshData : data_)
    {
        MeshDataBufferUniqueIDGroup meshDataBufferUniqueID;

        //名前
        std::string meshDataName = modelFileName_ + std::to_string(subMeshCnt);

        //ディスクをもとにバッファを生成
        meshDataBufferUniqueID.verticesGPUID        = tmpCreateBufferFunc.operator() < StandardVertexGPU >      
            (meshData.vertices.size(), meshDataName, "Vertices");

        meshDataBufferUniqueID.uniqueVertsIndicesID = tmpCreateBufferFunc.operator() < UniqueVertexIndexCPUGPU > 
            (meshData.uniqueVertexIndices.size(), meshDataName, "UniqueVertsIndices");

        meshDataBufferUniqueID.meshletsID           = tmpCreateBufferFunc.operator() < MeshletCPUGPU >           
            (meshData.meshlets.size(), meshDataName, "Meshlets");

        meshDataBufferUniqueID.primIndicesID        = tmpCreateBufferFunc.operator() < PrimitiveIndexCPUGPU >   
            (meshData.primitiveIndices.size(), meshDataName, "PrimIndices");

        meshDataBufferUniqueIDContainer.emplace_back(meshDataBufferUniqueID);

        //メッシュデータ番地を格納
        meshDataIDContainer.emplace_back(meshDataID_);
        //総メッシュデータ数をインクリメント
        meshDataID_ += MeshDataID(1);
    }

    //モデルのファイル名とメッシュデータIDを紐づける
    allocator_->LinkModelFileNameToMeshDataID
    (
        MeshContext::ModelSlotAllocator::CreateModelDataLicence{},
        modelFileName_, 
        meshDataIDContainer
    );

    //バッファコレクターに生成したバッファを仕分けしてもらう
    bufferCollector_->Distribute();

    //メッシュデータのバッファユニークID群を返す
    return meshDataBufferUniqueIDContainer;

}


