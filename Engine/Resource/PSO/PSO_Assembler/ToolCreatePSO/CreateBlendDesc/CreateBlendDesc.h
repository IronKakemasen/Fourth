#pragma once
#include "../../PipelineStateDesc.h"


//複数のカラーバッファに対応したブレンドディスク生成機
struct CreateBlendDesc
{
	///本丸
	CD3DX12_BLEND_DESC Create(const PipelineStateDesc::RenderTargetDesc& desc_);

private:

	//共通項目の設定
	void SetCommonDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_);
	//ブレンドモードに応じた設定
	void SetSpecificDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_, RenderStateComponent::BlendMode blendMode_);
};

