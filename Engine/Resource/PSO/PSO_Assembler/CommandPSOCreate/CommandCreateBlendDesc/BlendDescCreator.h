#pragma once
#include "../../../RenderState.h"


//複数のカラーバッファに対応したブレンドディスク生成機
class BlendDescCreator
{
	template<typename... BlendModes>
	D3D12_BLEND_DESC CreateBlendDesc(BlendModes... blendModes)
	{
		D3D12_BLEND_DESC blendDesc;

		auto const kNumArgs = sizeof...(blendModes);

		blendDesc.IndependentBlendEnable = FALSE;
		blendDesc.AlphaToCoverageEnable = FALSE;
		RenderStateComponent::BlendMode ary[] = { blendModes... };

		for (int i = 0;i < kNumArgs;++i)
		{
			//共通設定
			SetCommonDetails(&blendDesc.RenderTarget[i]);
			//ブレンドモードごとの設定
			SetSpecificDetails(&blendDesc.RenderTarget[i], ary[i]);
		}

		return blendDesc;
	}

private:

	//共通項目の設定
	void SetCommonDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_);
	//ブレンドモードに応じた設定
	void SetSpecificDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_, RenderStateComponent::BlendMode blendMode_);
};

