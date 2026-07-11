#pragma once

namespace RenderPassComponent  
{
	///RenderPathを構成する各ステージ
	enum class Pass
	{
		kCreateSceneTexture,

		
		kFinal
		,kCount

	};

    enum class DepthEnable
    {
        kDisable,
        kEnable
        , kCount
    };

    enum class DepthTest
    {
        kLessEqual,
        kGreaterEqual
        , kCount
    };

    inline D3D12_COMPARISON_FUNC Convert(DepthTest depthTest_)
    {
        return (depthTest_ == DepthTest::kGreaterEqual) ? D3D12_COMPARISON_FUNC_GREATER_EQUAL : D3D12_COMPARISON_FUNC_LESS_EQUAL;
    }

}

struct RenderPassState
{
    RenderPassComponent::Pass pass;
    RenderPassComponent::DepthTest depthTest;
    RenderPassComponent::DepthEnable depthEnable;
};