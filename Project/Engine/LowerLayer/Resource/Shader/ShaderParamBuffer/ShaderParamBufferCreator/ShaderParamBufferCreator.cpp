#include "PreCompileHeader.h"
#include "ShaderParamBufferCreator.h"
#include "../ShaderParamDispathcer/ShaderParamDispatcher.h"


//外部
#include "../../../../Buffer/BufferDefinition/BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"
#include "../../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../Buffer/BufferContextToolsInclude.h"
#include "../../../../Buffer/BufferContextDiplomats.h"

namespace
{
	auto const fileName = "ShaderParamBufferCreator.cpp";
}


ShaderContext::ShaderParamBufferCreator::ShaderParamBufferCreator
(
	NexusFieldProof proof_,
	ShaderParamDispatcher& shaderParamDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	shaderParamArrBufferCache.reserve((UINT)ShaderParam::Type::kCount);

	//shaderParam配列のバッファを作成
	CreateShaderParamsBuffer<ShaderParam::Type::kGridLine>(shaderParamDispatcher_, bufferContextDiplomat_);

	//作成したシェーダーパラメーター配列のsrvHeapIndexをキャッシュに登録してあるので、
	//それをもとにシェーダーパラメーター配列のsrvHeapIndex群のバッファを作成。
	//そのバッファのポインタを返す
	auto* shaderParamArrSrvIndexGroupBuffer = CreateShaderParamArrSrvIndexGroupBuffer(shaderParamDispatcher_, bufferContextDiplomat_);

	//ShaderParamArrSrvIndexGroupBufferの中身は不動なのでここでかきこんじゃう
	WriteShaderParamArrSrvIndex(shaderParamArrSrvIndexGroupBuffer);

	//そのsrvHeapIndexのグローバル定数バッファを作成
	CreateShaderParamSrvIndexGroupCBuffer(shaderParamArrSrvIndexGroupBuffer, bufferContextDiplomat_);
}


void ShaderContext::ShaderParamBufferCreator::CreateShaderParamSrvIndexGroupCBuffer
(
	GPUBufferBehavior* shaderParamArrSrvIndexGroupBuffer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//定数バッファ作成コマンドをもらう
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licence;
	auto createCBufferCmd = bufferContextDiplomat_.Access<BufferContext::CmdProvider>()->
		Provide<BufferContextCmds::CreateCBufferCmd>(licence);

	//srvHeapIndexを抽出
	IReadable* readableBuffer = static_cast<IReadable*>(static_cast<UploadStructuredBuffer*>(shaderParamArrSrvIndexGroupBuffer_));

	//定数バッファ生成コマンドで生成する
	auto cBufferID_cBuffer = createCBufferCmd("ShaderParamArrSrvIndexGroup", UINT(sizeof(SRVHeapIndex)), (UINT)ConstantBuffers::ConstantBufferBindSlots::kShaderParamArrSrvIndices);

	//その定数バッファのマップしたポインタにデータを書き込む
	//中身は不動なので、２面分書いちゃう
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ readableBuffer->OutProperSRVHeapIndex(0) ,readableBuffer->OutProperSRVHeapIndex(1) }
	);

}

void ShaderContext::ShaderParamBufferCreator::WriteShaderParamArrSrvIndex(GPUBufferBehavior* shaderParamArrSrvIndexGroupBuffer_)
{
	//書き込みさきバッファ
	auto* dstWriteBuf = static_cast<UploadStructuredBuffer*>(shaderParamArrSrvIndexGroupBuffer_);

	//詰め込み先データ両面分
	ShaderParam::ShaderParamArrSrvIndexGroupCPUGPU dataFrame0;
	ShaderParam::ShaderParamArrSrvIndexGroupCPUGPU dataFrame1;

	auto* dataFirstPtr0 = reinterpret_cast<SRVHeapIndex*>(&dataFrame0.gridLineSrv);
	auto* dataFirstPtr1 = reinterpret_cast<SRVHeapIndex*>(&dataFrame1.gridLineSrv);


	for (UINT n = 0; n < (UINT)ShaderParam::Type::kCount; ++n)
	{
		//srvHeapIndexを抽出ため
		IReadable* readableBuffer = 
			static_cast<IReadable*>(static_cast<UploadStructuredBuffer*>(shaderParamArrBufferCache[n]));

		//表裏２面分書き込む
		*(dataFirstPtr0 + n) = readableBuffer->OutProperSRVHeapIndex(0);
		*(dataFirstPtr1 + n) = readableBuffer->OutProperSRVHeapIndex(1);
	}


	dstWriteBuf->WriteInBoth<ShaderParam::ShaderParamArrSrvIndexGroupCPUGPU>
	(
		{ 
			dataFrame0,
			dataFrame1
		}
	);

}

GPUBufferBehavior* ShaderContext::ShaderParamBufferCreator::CreateShaderParamArrSrvIndexGroupBuffer
(
	ShaderParamDispatcher& shaderParamDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		shaderParamSequence == ShaderParam::Type::kCount,
		"ShaderParamArrバッファの作成数が足りない",
		fileName
	);

	//BufferCreatorを借りる
	auto bufferToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
	auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);

	//シェーダーパラメーター配列バッファはダブルバッファなので、srvheapIndexは2つ
	//その保管先も2面分ということでUploadStructuredBufferでいく
	UploadStructuredBufferDescription desc
	(
		(UINT)sizeof(ShaderParam::ShaderParamArrSrvIndexGroupCPUGPU),
		1,
		0
	);

	//シェーダーパラメーター配列のsrv群のバッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, "ShaderParamArrSrvIndexGroup");

	return id_buffer.second;
}



template<ShaderParam::Type type>
void ShaderContext::ShaderParamBufferCreator::CreateShaderParamsBuffer
(
	ShaderParamDispatcher& shaderParamDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		shaderParamSequence == type,
		"ShaderParamArrバッファの作成順序がおかしい",
		fileName
	);

	shaderParamSequence = ShaderParam::Type((UINT)shaderParamSequence + 1);


	auto bufferToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
	auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);


	//別のタイミングで描画対象ごとに上書きしたいバッファなので
	UploadStructuredBufferDescription desc
	(
		(UINT)sizeof(ShaderParamDispatcher::ShaderParamTraits<type>::dataType),
		ShaderParamDispatcher::ShaderParamTraits<type>::kReserveSize,
		0
	);

	//シェーダーパラメーターの配列バッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, ShaderParamDispatcher::ShaderParamTraits<type>::kName);

	//登録
	shaderParamDispatcher_.ImportShaderParamsBufferID<type>(ShaderParamDispatcher::LocalKey{}, id_buffer.first);

	//キャッシュに登録
	shaderParamArrBufferCache.emplace_back(id_buffer.second);
}

template
void ShaderContext::ShaderParamBufferCreator::CreateShaderParamsBuffer<ShaderParam::Type::kGridLine>
(
	ShaderParamDispatcher& shaderParamDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
);
