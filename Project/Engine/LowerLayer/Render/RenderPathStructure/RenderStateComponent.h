#pragma once

namespace RenderStateComponent
{
    enum class BlendMode
    {
        kOpaque,
        kAlphaBlend,
        kAdditive
    };

    enum class FillMode
    {
        kWireFrame,
        kSolid
        ,kCount
    };

    enum class CullMode
    {
        kNone,
        kFront,
        kBack
        ,kCount
    };


    enum class DepthEnable
    {
        kDisable, 
        kEnable
        ,kCount
    };

    enum class DepthTest
    {
        kLessEqual,
        kGreaterEqual
        ,kCount
    };

    //モデル一つにつき１定義のみ
    struct Uniqued
    {
        RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
    };

    //複数定義可能
    struct Flexible
    {
        RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kOpaque;
    };



    inline D3D12_FILL_MODE Convert(FillMode fillMode_)
    {
        return (fillMode_ == FillMode::kSolid) ? D3D12_FILL_MODE_SOLID : D3D12_FILL_MODE_WIREFRAME;
    }

    inline D3D12_CULL_MODE Convert(CullMode cullMode_)
    {
        D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK;

        if (cullMode_ == CullMode::kFront) cullMode = D3D12_CULL_MODE_FRONT;
        else if(cullMode_ == CullMode::kNone) cullMode = D3D12_CULL_MODE_NONE;

        return cullMode;
    }

    inline D3D12_COMPARISON_FUNC Convert(DepthTest depthTest_)
    {
        D3D12_COMPARISON_FUNC comparisonFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;

        return (depthTest_ == DepthTest::kGreaterEqual) ? D3D12_COMPARISON_FUNC_GREATER_EQUAL : D3D12_COMPARISON_FUNC_LESS_EQUAL;
    }
}

