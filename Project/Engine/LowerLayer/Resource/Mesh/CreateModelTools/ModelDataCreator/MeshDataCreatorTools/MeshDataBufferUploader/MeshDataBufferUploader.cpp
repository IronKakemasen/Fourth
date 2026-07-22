#include "PreCompileHeader.h"
#include "MeshDataBufferUploader.h"
#include "../ModelDataTransducer/ModelDataTransducer.h"


//外部
#include "../../../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"

namespace
{
    auto const fileName = "MeshDataBufferUploader.cpp";
}


void MeshContext::ModelDataCreator::MeshDataBufferUploader::CopyAndUploadBuffer
(
	const std::vector<ResourceMesh>& data_,
	const std::vector<MeshDataStructuredBufferGroup>& bufferPtrGroups_,
	BufferContext::BufferUploader* bufferUploader_
)
{
    size_t numMeshData = data_.size();
    ErrorMessageOutput::Assert::DetectError
    (
        numMeshData == bufferPtrGroups_.size(),
        "メッシュデータとそれのポインタのの種類数がおなじじゃない",
        fileName
    );

    //CPUにマッピングしてアップロードする
    for (size_t i = 0;i < numMeshData;++i)
    {

    }

}
