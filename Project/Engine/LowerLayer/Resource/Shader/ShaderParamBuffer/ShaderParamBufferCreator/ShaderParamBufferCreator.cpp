#include "PreCompileHeader.h"
#include "ShaderParamBufferCreator.h"
#include "../ShaderParamDispathcer/ShaderParamDispatcher.h"


//外部
#include "../../../../Buffer/BufferDefinition/BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../../Buffer/BufferContextToolsInclude.h"
#include "../../../../Buffer/BufferContextDiplomats.h"

BufferUniqueID ShaderContext::ShaderParamBufferCreator::CreateShaderParamSrvIndexGroupBuffer(BufferContextDiplomat& bufferContextDiplomat_)
{
	//BufferCreatorを借りる
	auto bufferToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
	auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);

	//別のタイミングで描画対象ごとに上書きしたいバッファなので
	UploadStructuredBufferDescription desc
	(
		(UINT)sizeof(ShaderParam::ShaderParamSrvIndexGroupCPUGPU),
		shaderParamSrvIndexGroupBufferSize,
		0
	);

	//シェーダーパラメーターsrv群コンテナのバッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, "ShaderParamSrvIndexGroup");

	return id_buffer.first;
}



template<ShaderParam::Type type>
BufferUniqueID ShaderContext::ShaderParamBufferCreator::CreateBuffer(BufferContextDiplomat& bufferContextDiplomat_)
{
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

	//最低でも確保しなくてはならないシェーダーパラメーターSRV群コンテナバッファのサイズを更新
	shaderParamSrvIndexGroupBufferSize =
		Comparison::Max(shaderParamSrvIndexGroupBufferSize, ShaderParamDispatcher::ShaderParamTraits<type>::kReserveSize);

	//シェーダーパラメーターの配列バッファを作成
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, ShaderParamDispatcher::ShaderParamTraits<type>::kName);

	return id_buffer.first;
}

template
BufferUniqueID ShaderContext::ShaderParamBufferCreator::CreateBuffer<ShaderParam::Type::kGridLine>(BufferContextDiplomat& bufferContextDiplomat_);
