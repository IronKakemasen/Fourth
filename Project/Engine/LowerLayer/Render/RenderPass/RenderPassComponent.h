#pragma once

namespace RenderPassComponent  
{
	///RenderPathを構成する各ステージ
    ///PSOを一意に決定するため、Pass生成でクラスを紐づけるために利用
    ///これにバッファの情報から深度テスト方法などの情報が詰まってるといっていい
	enum class Pass
	{
		kSceneTextureCreatorOpaque,
        kSceneTextureCompositor
		
		
		,kCount,
        kEnd
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

    inline const D3D12_COMPARISON_FUNC Convert(DepthTest depthTest_)
    {
        return (depthTest_ == DepthTest::kGreaterEqual) ? D3D12_COMPARISON_FUNC_GREATER_EQUAL : D3D12_COMPARISON_FUNC_LESS_EQUAL;
    }

    inline std::string const DepthTestString(DepthTest depthTest_)
    {
        return (depthTest_ == DepthTest::kGreaterEqual) ? "GreaterEqual" : "LessEqual";
    }

}

