#pragma once
#include "../MaterialContext.h"


//外部
#include "../../../../../../Assets/Shared/Material.h"

class GPUBufferBehavior;

class MaterialContext::MaterialBufferCreator
{
public:

	MaterialBufferCreator
	(
		NexusFieldProof proof_,
		MaterialIndexDispatcher& materialIndexDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	//描画対象固有のシェーダーパラメーター最大数
	UINT shaderParamIndexGroupBufferSize =
		(UINT)ProjectConfig::Render::BufferSize::kShaderParamSrvGroupContainer;

	//shaderParamArrバッファのキャッシュ
	std::vector<GPUBufferBehavior*> shaderParamArrBufferCache;

	//ちょいと雑だが、呼び出しシーケンスチェックのため
	Material::Type shaderParamSequence = Material::Type::kGridLine;

	//描画対象固有のシェーダーパラメータ配列のバッファをサイズ分作成
	template<Material::Type type>
	void CreateShaderParamsBuffer
	(
		MaterialIndexDispatcher& materialIndexDispatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	//それらのsrvHeapIndex群のバッファも作成する
	GPUBufferBehavior* CreateShaderParamArrSrvIndexGroupBuffer
	(
		MaterialIndexDispatcher& materialIndexDispatcher_,
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

