#include "PreCompileHeader.h"
#include "MeshDataSRVHeapIndexGroupContainerBufferCreator.h"

//外部
#include "../../../../../Buffer/BufferContextToolsInclude.h"

//ほんとはstaticStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/BufferInterface.h"


using namespace StructuredBufferDataDefinition;

void ModelContext::ModelDataCreator::MeshDataSRVHeapIndexGroupContainerBufferCreator::Create
(
	const std::vector<MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
	BufferContext::BufferCreator* bufferCreator_,
	BufferContext::BufferUploader* uploader_,
	BufferContext::ConstantBufferCreator* cBufferCreator_
)
{
	std::string const bufferName = "MeshDataSRVHeapIndexGroupContainer";

	UINT srcContainerSize = (UINT)tmpMeshDataSRVHeapIndexGroupContainer_.size();

	StaticStructuredBufferDescription desc
	(
		sizeof(MeshDataSRVHeapIndexGroupGPUCPU),
		srcContainerSize,
		0
	);

	//バッファ生成
	auto uniqueID_buffer = bufferCreator_->CreateWithBuffer(desc, bufferName);

	//アップロードする
	uploader_->RegisterBuffer(uniqueID_buffer.first, srcContainerSize, tmpMeshDataSRVHeapIndexGroupContainer_.data());

	//srvHeapIndexを抽出
	IReadable* readableBuffer = static_cast<IReadable*>(uniqueID_buffer.second);
	//そのコンスタントバッファを生成し、データを入力する
	auto cBufferID_cBuffer = cBufferCreator_->Create(bufferName, UINT(sizeof(SRVHeapIndex)), 0);
	for (int i = 0;i < (int)ProjectConfig::Render::NumBuffer::kDoubleBuffer;++i)
	{
		auto* mappedPtr = cBufferID_cBuffer.second->GetMappedPtr<SRVHeapIndex>(i);
		*mappedPtr = readableBuffer->OutProperSRVHeapIndex();
	}


}
