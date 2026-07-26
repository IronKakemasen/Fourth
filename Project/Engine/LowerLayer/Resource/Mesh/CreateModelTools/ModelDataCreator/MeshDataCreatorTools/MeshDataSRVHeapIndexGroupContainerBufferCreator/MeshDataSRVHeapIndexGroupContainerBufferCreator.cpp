#include "PreCompileHeader.h"
#include "MeshDataSRVHeapIndexGroupContainerBufferCreator.h"

//外部
#include "../../../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"

#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
//ほんとはstaticStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/BufferInterface.h"

using namespace StructuredBufferDataDefinition;

void MeshContext::ModelDataCreator::MeshDataSRVHeapIndexGroupContainerBufferCreator::Create
(
	const std::vector<MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
	BufferContext::BufferCreator* bufferCreator_,
	BufferContext::BufferCollector* bufferCollector_,
	BufferContext::BufferDispatcher* dispatcher_,
	BufferContext::BufferUploader* uploader_,
	MeshContext::ModelSlotAllocator* allocator_
)
{
	UINT srcContainerSize = (UINT)tmpMeshDataSRVHeapIndexGroupContainer_.size();

	StaticStructuredBufferDescription desc
	(
		sizeof(MeshDataSRVHeapIndexGroupGPUCPU),
		srcContainerSize,
		0
	);

	//バッファ生成
	BufferUniqueID uniqueID = bufferCreator_->Create(desc, "MeshDataSRVHeapIndexGroupContainer");
	bufferCollector_->Distribute();

	//アップロードする
	uploader_->RegisterBuffer(uniqueID, srcContainerSize, tmpMeshDataSRVHeapIndexGroupContainer_.data());

	//srvHeapIndexを抽出
	StaticStructuredBuffer* buffer = static_cast<StaticStructuredBuffer*>(dispatcher_->Dispatch(uniqueID));
	IReadable* readableBuffer = static_cast<IReadable*>(buffer);

	//アロケータにこのバッファのsrvHeapIndexを記録させる
	allocator_->SetMeshDataSRVHeapIndexGroupContainerSRVHeapIndex
	(
		MeshContext::ModelSlotAllocator::HandleLicence{}, 
		readableBuffer->OutProperSRVHeapIndex()
	);



}
