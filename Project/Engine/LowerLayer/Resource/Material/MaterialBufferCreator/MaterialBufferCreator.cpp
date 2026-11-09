#include "PreCompileHeader.h"
#include "MaterialBufferCreator.h"


#include "../MaterialIndexDispatcher/MaterialIndexDispatcher.h"


//外部
#include "../../../Buffer/BufferDefinition/BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"
#include "../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../Buffer/BufferContextToolsInclude.h"
#include "../../../Buffer/BufferContextDiplomats.h"

namespace
{
	auto const fileName = "MaterialBufferCreator.cpp";
}


MaterialContext::MaterialBufferCreator::MaterialBufferCreator
(
	NexusFieldProof proof_,
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	shaderParamArrBufferCache.reserve((UINT)Material::kNumParamExists);

	//Material配列のバッファを作成
	CreateShaderParamsBuffer<Material::Type::kStandard>(materialIndexDispatcher_, bufferContextDiplomat_);
	CreateShaderParamsBuffer<Material::Type::kGridLine>(materialIndexDispatcher_, bufferContextDiplomat_);

	//作成したシェーダーパラメーター配列のsrvHeapIndexをキャッシュに登録してあるので、
	//それをもとにシェーダーパラメーター配列のsrvHeapIndex群のバッファを作成。
	//そのバッファのポインタを返す
	auto* shaderParamArrSrvIndexGroupBuffer = CreateShaderParamArrSrvIndexGroupBuffer(materialIndexDispatcher_, bufferContextDiplomat_);

	//ShaderParamArrSrvIndexGroupBufferの中身は不動なのでここでかきこんじゃう
	WriteShaderParamArrSrvIndex(shaderParamArrSrvIndexGroupBuffer);

	//そのsrvHeapIndexのグローバル定数バッファを作成
	CreateShaderParamSrvIndexGroupCBuffer(shaderParamArrSrvIndexGroupBuffer, bufferContextDiplomat_);
}


void MaterialContext::MaterialBufferCreator::CreateShaderParamSrvIndexGroupCBuffer
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

void MaterialContext::MaterialBufferCreator::WriteShaderParamArrSrvIndex(GPUBufferBehavior* shaderParamArrSrvIndexGroupBuffer_)
{
	//書き込みさきバッファ
	auto* dstWriteBuf = static_cast<UploadStructuredBuffer*>(shaderParamArrSrvIndexGroupBuffer_);

	//詰め込み先データ両面分
	Material::MaterialArrSrvIndexGroupCPUGPU dataFrame0;
	Material::MaterialArrSrvIndexGroupCPUGPU dataFrame1;

	auto* dataFirstPtr0 = reinterpret_cast<SRVHeapIndex*>(&dataFrame0.standardSrv);
	auto* dataFirstPtr1 = reinterpret_cast<SRVHeapIndex*>(&dataFrame1.standardSrv);


	for (UINT n = 0; n < (UINT)Material::kNumParamExists; ++n)
	{
		//srvHeapIndexを抽出ため
		IReadable* readableBuffer =
			static_cast<IReadable*>(static_cast<UploadStructuredBuffer*>(shaderParamArrBufferCache[n]));

		//表裏２面分書き込む
		*(dataFirstPtr0 + n) = readableBuffer->OutProperSRVHeapIndex(0);
		*(dataFirstPtr1 + n) = readableBuffer->OutProperSRVHeapIndex(1);
	}


	dstWriteBuf->WriteInBoth<Material::MaterialArrSrvIndexGroupCPUGPU>
	(
		{
			dataFrame0,
			dataFrame1
		}
	);

}

GPUBufferBehavior* MaterialContext::MaterialBufferCreator::CreateShaderParamArrSrvIndexGroupBuffer
(
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		(UINT)shaderParamSequence == Material::kNumParamExists,
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
		(UINT)sizeof(Material::MaterialArrSrvIndexGroupCPUGPU),
		1,
		0
	);

	//シェーダーパラメーター配列のsrv群のバッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, "ShaderParamArrSrvIndexGroup");

	return id_buffer.second;
}



template<Material::Type type>
void MaterialContext::MaterialBufferCreator::CreateShaderParamsBuffer
(
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		shaderParamSequence == type,
		"ShaderParamArrバッファの作成順序がおかしい",
		fileName
	);

	shaderParamSequence = Material::Type((UINT)shaderParamSequence + 1);


	auto bufferToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
	auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);


	//別のタイミングで描画対象ごとに上書きしたいバッファなので
	UploadStructuredBufferDescription desc
	(
		(UINT)sizeof(Material::MaterialTypeTraits<type>::dataType),
		Material::MaterialTypeTraits<type>::kReserveSize,
		0
	);

	//シェーダーパラメーターの配列バッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, Material::MaterialTypeTraits<type>::kName);

	//登録
	materialIndexDispatcher_.ImportShaderParamsBufferID<type>(MaterialIndexDispatcher::LocalKey{}, id_buffer.first);

	//キャッシュに登録
	shaderParamArrBufferCache.emplace_back(id_buffer.second);
}




template
void MaterialContext::MaterialBufferCreator::CreateShaderParamsBuffer<Material::Type::kStandard>
(
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
);

template
void MaterialContext::MaterialBufferCreator::CreateShaderParamsBuffer<Material::Type::kGridLine>
(
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
);
