#pragma once
#include "../../ShaderContext.h"


//外部
#include "../../../../../../Assets/Shared/ShaderParam.h"


class ShaderContext::ShaderParamBufferCreator
{
public:

	ShaderParamBufferCreator
	(
		NexusFieldProof proof_,
		ShaderParamDispatcher& shaderParamDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//描画対象固有のシェーダーパラメータのバッファをサイズ分作成し、
	//それらパラメータのsrvHeapIndex群のコンテナのバッファも作成する。これは描画対象の数ぶん必要



private:

	//描画対象固有のシェーダーパラメーター最大数
	UINT shaderParamSrvIndexGroupBufferSize{};

	template<ShaderParam::Type type>
	BufferUniqueID CreateBuffer(BufferContextDiplomat& bufferContextDiplomat_);

	BufferUniqueID CreateShaderParamSrvIndexGroupBuffer(BufferContextDiplomat& bufferContextDiplomat_);

};

