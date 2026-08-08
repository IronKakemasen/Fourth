#include "PreCompileHeader.h"
#include "TransformMatrixContainerBufferCreator.h"
#include "../../../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

//外部
#include "../../../../../Buffer/BufferContextToolsInclude.h"

//ほんとはuploadStructuredBufferDescriptionだけでいいんだけど、文字列制限なのかインクルードできないので
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"
#include "../../../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../../../../../Assets/Shared/StructuredBuffer.h"


using namespace StructuredBufferDataDefinition;
using namespace ProjectConfig::Render;

void ModelContext::ModelDataCreator::TransformMatrixContainerBufferCreator::Create
(
	BufferContext::BufferCreator* bufferCreator_,
	BufferContextCmds::CreateCBufferCmd createCBufferCmd_,
	ModelDataBatcher* modelDataBatcher_
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

	//UploadStructuredBufferとして生成
	std::string const bufferName = "TransformMatrixContainer";
	auto bufferUnique_buffer = bufferCreator_->CreateWithBuffer(desc, bufferName);

	///ランタイムでTransformMatrixはもちろん更新するから、その索引用として
	///こいつのIDは頂戴する
	modelDataBatcher_->ImportBufferID<ModelDataBatcher::BufferIDType::kTransformMatrixContainer>
		(ModelDataBatcher::Local_InputBufferUniqueIDLicence{}, bufferUnique_buffer.first);

	//SRVHeapIndexを抽出
	auto* readableBuffer = static_cast<IReadable*>(bufferUnique_buffer.second);
	
	//そのコンスタントバッファを生成し、データを入力する
	///定数バッファはダブルバッファなので、それぞれに別々のsrvHeapIndexを入力する
	
	//バインドしているスロットはジェーソンファイルから読み込む
	auto const srcJsonFileKey = "WorldConstantBuffers";
	
	//バインドスロットを取得
	int const dstBindSlot = Miyajison::Get()->LoadData<int>(srcJsonFileKey, { bufferName,"BindSlot" });

	//定数バッファ生成コマンドで生成する
	auto cBufferID_cBuffer = createCBufferCmd_(bufferName, UINT(sizeof(SRVHeapIndex)), dstBindSlot);
	for (int i = 0;i < (int)ProjectConfig::Render::NumBuffer::kDoubleBuffer;++i)
	{
		auto* mappedPtr = cBufferID_cBuffer.second->GetMappedPtr<SRVHeapIndex>(i);
		*mappedPtr = readableBuffer->OutProperSRVHeapIndex(i);
	}

}
