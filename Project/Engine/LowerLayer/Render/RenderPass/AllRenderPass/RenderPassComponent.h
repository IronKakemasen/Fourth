#pragma once
#include "AllPassFwd.h"

namespace RenderPassComponent  
{
	///RenderPathを構成する各ステージ
	enum class Pass
	{
		kSceneTextureCreator

		
		
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

    inline D3D12_COMPARISON_FUNC Convert(DepthTest depthTest_)
    {
        return (depthTest_ == DepthTest::kGreaterEqual) ? D3D12_COMPARISON_FUNC_GREATER_EQUAL : D3D12_COMPARISON_FUNC_LESS_EQUAL;
    }


    RenderPassComponent::Pass PassNameToPassType(std::string const passName_);
    
    template<RenderPassComponent::Pass passType>
    struct PassTypeToPassClass;

}

template<>
struct RenderPassComponent::PassTypeToPassClass<RenderPassComponent::Pass::kSceneTextureCreator>
{
    using PassClass = SceneTextureCreator;
};
