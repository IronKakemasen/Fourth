#include "PreCompileHeader.h"
#include "PerDrawDataBufferCreator.h"
#include "../../../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

//外部
#include "../../../../../../Buffer/BufferContextToolsInclude.h"

//ほんとはuploadStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../../../../../Assets/Shared/StructuredBufferModelData.h"


using namespace StructuredBufferModelData;
using namespace ProjectConfig::Render;

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::CreatePerDrawConstntBuffer
(
	BufferContext::BufferCreator* bufferCreator_,
	BufferContextCmds::CreateCBufferCmd createCBufferCmd_,
	ModelDataBatcher* modelDataBatcher_
)
{
	Create<ModelDataBatcher::BufferType::kTransformMatrixContainer>(bufferCreator_, modelDataBatcher_);
	Create<ModelDataBatcher::BufferType::kMaterialContainer>(bufferCreator_, modelDataBatcher_);

}



std::array<SRVHeapIndex, UINT(ProjectConfig::Render::NumBuffer::kDoubleBuffer)>
ModelContext::ModelDataCreator::PerDrawDataBufferCreator::ExtractSrvHeapIndices(UploadStructuredBuffer* srcBuffer_)
{
	//SRVHeapIndexを抽出
	auto* readableBuffer = static_cast<IReadable*>(srcBuffer_);

	return 	{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) };
}

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::PackageInConstanrBuffer
(
	UploadStructuredBuffer* dstBuffer_,
	BufferContextCmds::CreateCBufferCmd& createCBufferCmd_,
	ConstantBuffers::ConstantBufferBindSlots dstSlot_
)
{
	//SRVHeapIndexを抽出
	auto* readableBuffer = static_cast<IReadable*>(dstBuffer_);

	//そのコンスタントバッファを生成し、データを入力する
	///定数バッファはダブルバッファなので、それぞれに別々のsrvHeapIndexを入力する

	//定数バッファ生成コマンドで生成する
	auto cBufferID_cBuffer = createCBufferCmd_
	(
		dstBuffer_->WatchName(),
		UINT(sizeof(SRVHeapIndex)),
		dstSlot_
	);

	//その定数バッファのマップしたポインタにデータを書き込む
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) }
	);

}


std::pair<BufferUniqueID,UploadStructuredBuffer*> ModelContext::ModelDataCreator::PerDrawDataBufferCreator::CreateBuffer
(
	DescParam const& descParam_,
	BufferContext::BufferCreator* bufferCreator_
)
{
	//まずTransformMatrixのUploadStructuredBufferを作成するためのディスクリプションの生成
	///！！！！！UploadStructuredBufferはダブルバッファなのでsrvは2個作られる！！！！！
	UploadStructuredBufferDescription desc
	(
		descParam_.sizeOfStructure,
		descParam_.sizeOfArr,
		0
	);

	auto bufferUnique_buffer = bufferCreator_->CreateWithBuffer(desc, descParam_.bufferName);

	return bufferUnique_buffer;
}
