#include "PreCompileHeader.h"
#include "GlobalConstantBufferPackager.h"


//外部
#include "../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../Buffer/GlobalConstantBuffers/GlobalConstantBufferCreator/GlobalConstantBufferCreator.h"
#include "../../../Buffer/BufferDefinition/BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"
#include "../../../Buffer/BufferContextDiplomat/BufferDiplomatIncludes.h"

void TextureContext::TextureBufferCreator::GlobalConstantBufferPackager::Package
(
	std::vector<SRVHeapIndex> const& indices_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//バッファコンテキストのツールレンダーからいろんなツールを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licenceManageBuffer{};
	auto* bufferCreator = toolLender->Lend<BufferContext::BufferCreator>(licenceManageBuffer);
	auto* bufferUploader = toolLender->Lend<BufferContext::BufferUploader>(licenceManageBuffer);

	//定数バッファ生成コマンドを提供してもらう
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licenceCmd;
	auto* cmdProvider = bufferContextDiplomat_.Access<BufferContext::CmdProvider>();
	auto createCBufferCmd = cmdProvider->Provide<BufferContextCmds::CreateCBufferCmd>(licenceCmd);


	//まずはindicesのstaticStructuredBufferを作ってアップロードする
	//ディスク作って
	StaticStructuredBufferDescription desc((UINT)sizeof(SRVHeapIndex), (UINT)indices_.size(), 0);
	std::string const bufferName = "TextureIndices";
	
	//バッファ生成して
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, bufferName);
	//srvHeapIndexを抽出
	IReadable* readableBuffer = static_cast<IReadable*>(id_buffer.second);

	//アップロードリストに登録
	bufferUploader->RegisterBuffer(id_buffer.first, (UINT)indices_.size(), indices_.data());

	//そのバッファのコンスタントバッファを生成し
	auto cBufferID_cBuffer = 
		createCBufferCmd(bufferName, (UINT)(sizeof(SRVHeapIndex)), ConstantBuffers::ConstantBufferBindSlots::kTextureContainer);

	//データを書き込む
	//その定数バッファのマップしたポインタにデータを書き込む
	///定数バッファはダブルバッファなので、それぞれに別々のsrvHeapIndexを入力する
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) }
	);


}
