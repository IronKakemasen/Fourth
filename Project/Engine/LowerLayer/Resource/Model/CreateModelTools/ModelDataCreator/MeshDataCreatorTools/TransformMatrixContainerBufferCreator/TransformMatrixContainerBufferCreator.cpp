#include "PreCompileHeader.h"
#include "TransformMatrixContainerBufferCreator.h"

#include "../../../ModelSlotAllocator/ModelSlotAllocator.h"
//外部
#include "../../../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
//ほんとはuploadStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"

using namespace StructuredBufferDataDefinition;
using namespace ProjectConfig::Render;

void ModelContext::ModelDataCreator::TransformMatrixContainerBufferCreator::Create
(
	ModelContext::ModelSlotAllocator* slotAllocator_,
	BufferContext::BufferCreator* bufferCreator_,
	BufferContext::BufferCollector* bufferCollector_,
	BufferContext::BufferDispatcher* bufferDispatcher_
)
{
	//まずTransformMatrixのUploadStructuredBufferを作成するためのディスクリプションの生成
	///データ型はTransformMatrixCPUGPU
	///用意する数はkSizeOfTransformMatrixBufferArray個分 = 最大でモデルを描画できる数
	///！！！！！UploadStructuredBufferはダブルバッファなのでsrvは2個作られる！！！！！
	UploadStructuredBufferDescription desc
	(
		UINT(sizeof(TransformMatrixCPUGPU)),
		UINT(GlobalBufferTableSetting::kSizeOfTransformMatrixBufferArray),
		0
	);

	BufferUniqueID TransformMatrixContainerBufferID = bufferCreator_->Create(desc,"TransformMatrix");
	bufferCollector_->Distribute();

	//SRVHeapIndexを抽出
	auto* TransformMatrixContainerBuffer = 
		static_cast<UploadStructuredBuffer*>(bufferDispatcher_->Dispatch(TransformMatrixContainerBufferID));
	auto* iReadable_TransformMatrixContainerBuffer = static_cast<IReadable*>(TransformMatrixContainerBuffer);

	//それらを保存する
	slotAllocator_->SetTransformMatrixConatinerSrvHeapIndices
	(
		ModelContext::ModelSlotAllocator::HandleLicence{},
		{ iReadable_TransformMatrixContainerBuffer->OutProperSRVHeapIndex(0),iReadable_TransformMatrixContainerBuffer->OutProperSRVHeapIndex(1) }
	);
}
