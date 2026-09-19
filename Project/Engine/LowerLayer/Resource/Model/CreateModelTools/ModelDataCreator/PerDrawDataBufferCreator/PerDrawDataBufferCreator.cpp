#include "PreCompileHeader.h"
#include "PerDrawDataBufferCreator.h"
#include "../../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

//外部
#include "../../../../../Buffer/BufferContextToolsInclude.h"

//ほんとはuploadStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../Buffer/BufferDefinition/AllBuffersInclude.h"


using namespace ConstantBuffers;
using namespace StructuredBufferModelData;
using namespace ProjectConfig::Render;
using namespace BufferContextCmds;

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::CreatePerDrawConstntBuffer
(
	BufferContext::BufferCreator* bufferCreator_,
	ModelDataBatcher* modelDataBatcher_,
	CreateCBufferCmd& createCBufferCmd_
)
{
	Create<ConstantBufferBindSlots::kTransformMatrixContainer>(bufferCreator_, modelDataBatcher_, createCBufferCmd_);
	Create<ConstantBufferBindSlots::kMaterialContainer>(bufferCreator_, modelDataBatcher_, createCBufferCmd_);

	//最後に、perDrawDataのコンスタントバッファを作る
	CreatePerDrawCBuffer(createCBufferCmd_);

}

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::CreatePerDrawCBuffer(CreateCBufferCmd& createCBufferCmd_)
{
	//もちろん中身はモデルに依存するので、ドローコール時に書き込む
	auto cBufferID_cBuffer = createCBufferCmd_
	(
		"PerDrawIndices",
		UINT(sizeof(PerDrawIndicesCPUGPU)),
		UINT(RootConstantsBindSlots::kPerDrawIndices)
	);

}



std::array<SRVHeapIndex, UINT(NumBuffer::kDoubleBuffer)>
ModelContext::ModelDataCreator::PerDrawDataBufferCreator::ExtractSrvHeapIndices(UploadStructuredBuffer* srcBuffer_)
{
	//SRVHeapIndexを抽出
	auto* readableBuffer = static_cast<IReadable*>(srcBuffer_);

	return 	{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) };
}

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::PackageInConstanrBuffer
(
	UploadStructuredBuffer* dstBuffer_,
	CreateCBufferCmd& createCBufferCmd_,
	ConstantBufferBindSlots dstSlot_
)
{
	///定数バッファはダブルバッファなので、それぞれに別々のsrvHeapIndexを入力する

	//定数バッファ生成コマンドで生成する
	auto cBufferID_cBuffer = createCBufferCmd_
	(
		dstBuffer_->WatchName(),
		UINT(sizeof(SRVHeapIndex)),
		(UINT)dstSlot_
	);

	//定数バッファにデータを書き込む
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>(ExtractSrvHeapIndices(dstBuffer_));
}


std::pair<BufferUniqueID,UploadStructuredBuffer*> ModelContext::ModelDataCreator::PerDrawDataBufferCreator::CreateBuffer
(
	DescImitation const& descImitation_,
	BufferContext::BufferCreator* bufferCreator_
)
{
	//まずTransformMatrixのUploadStructuredBufferを作成するためのディスクリプションの生成
	///！！！！！UploadStructuredBufferはダブルバッファなのでsrvは2個作られる！！！！！
	UploadStructuredBufferDescription desc
	(
		descImitation_.sizeOfStructure,
		descImitation_.sizeOfArr,
		0
	);

	auto bufferUnique_buffer = bufferCreator_->CreateWithBuffer(desc, descImitation_.bufferName);

	return bufferUnique_buffer;
}
