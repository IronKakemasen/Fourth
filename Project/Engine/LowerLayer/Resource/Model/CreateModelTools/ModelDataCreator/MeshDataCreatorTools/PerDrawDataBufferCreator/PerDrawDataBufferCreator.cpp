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

void ModelContext::ModelDataCreator::PerDrawDataBufferCreator::Create
(
	BufferContext::BufferCreator* bufferCreator_,
	BufferContextCmds::CreateCBufferCmd createCBufferCmd_,
	ModelDataBatcher* modelDataBatcher_
)
{
	//まずTransformMatrixのUploadStructuredBufferを作成するためのディスクリプションの生成
	///データ型はTransformMatrixCPUGPU
	///用意する数はkSizeOfTransformMatrixArrayBuffer個分 = 最大でモデルを描画できる数
	///！！！！！UploadStructuredBufferはダブルバッファなのでsrvは2個作られる！！！！！
	UploadStructuredBufferDescription desc
	(
		UINT(sizeof(TransformMatrixCPUGPU)),
		UINT(GlobalBufferTableSetting::kSizeOfTransformMatrixContainerBuffer),
		0
	);

	//UploadStructuredBufferとして生成
	std::string const bufferName = "TransformMatrixContainer";
	auto bufferUnique_buffer = bufferCreator_->CreateWithBuffer(desc, bufferName);

	///ランタイムでTransformMatrixはもちろん更新するから、その索引用として
	///こいつのIDは頂戴する
	modelDataBatcher_->ImportPerDrawBufferID<ModelDataBatcher::BufferType::kTransformMatrixContainer>
		(ModelDataBatcher::Local_InputBufferUniqueIDLicence{}, bufferUnique_buffer.first);

	//SRVHeapIndexを抽出
	auto* readableBuffer = static_cast<IReadable*>(bufferUnique_buffer.second);
	
	//そのコンスタントバッファを生成し、データを入力する
	///定数バッファはダブルバッファなので、それぞれに別々のsrvHeapIndexを入力する

	//定数バッファ生成コマンドで生成する
	auto cBufferID_cBuffer = createCBufferCmd_(bufferName, UINT(sizeof(SRVHeapIndex)), ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer);
	
	//その定数バッファのマップしたポインタにデータを書き込む
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) }
	);



}
