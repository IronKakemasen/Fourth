#pragma once
#include "../../ShaderContext.h"


//外部
#include "../../../../../../Assets/Shared/ShaderParam.h"

class GPUBufferBehavior;

class ShaderContext::ShaderParamBufferCreator
{
public:

	ShaderParamBufferCreator
	(
		NexusFieldProof proof_,
		ShaderParamDispatcher& shaderParamDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	//描画対象固有のシェーダーパラメーター最大数
	UINT shaderParamIndexGroupBufferSize = 
		(UINT)ProjectConfig::Render::BufferSize::kShaderParamSrvGroupContainer;

	//shaderParamArrバッファのキャッシュ
	std::vector<GPUBufferBehavior*> shaderParamArrBufferCache;

	//ちょいと雑だが、呼び出しシーケンスチェックのため
	ShaderParam::Type shaderParamSequence = ShaderParam::Type::kGridLine;

	//描画対象固有のシェーダーパラメータ配列のバッファをサイズ分作成
	template<ShaderParam::Type type>
	void CreateShaderParamsBuffer
	(
		ShaderParamDispatcher& shaderParamDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	//それらのsrvHeapIndex群のバッファも作成する
	GPUBufferBehavior* CreateShaderParamArrSrvIndexGroupBuffer
	(
		ShaderParamDispatcher& shaderParamDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//ShaderParamArrバッファの表裏２面分のsrvIndexを書き込む
	void WriteShaderParamArrSrvIndex(GPUBufferBehavior* shaderParamArrSrvIndexGroupBuffer_);

	//ShaderParamArrSrvIndexGroupのSrvIndexのグローバル定数バッファを作成する
	void CreateShaderParamSrvIndexGroupCBuffer
	(
		GPUBufferBehavior* shaderParamArrSrvIndexGroupBuffer_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

};


////最低でも確保しなくてはならないシェーダーパラメーターSRV群コンテナバッファのサイズを更新
//shaderParamIndexGroupBufferSize =
//Comparison::Max(shaderParamIndexGroupBufferSize, ShaderParamDispatcher::ShaderParamTraits<type>::kReserveSize);
