#pragma once

namespace RenderStateComponent
{
    enum class BlendMode
    {
        kOpaque,
        kAlphaBlend,
        kAdditive
        ,kCount
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

    //モデルクラス専用の描画パス選択。全てのパスで描画するわけじゃないからさ
    enum class RenderPass : uint32_t
    {
        kNone = 0,
        kSceneTexture = 1 << 0,  
        kShadow = 1 << 1,  


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

    constexpr RenderPass operator&(RenderPass lhs_, RenderPass rhs_)
    {
        return RenderPass(uint32_t(lhs_) & uint32_t(rhs_));
    }

    constexpr RenderPass operator|(RenderPass lhs_, RenderPass rhs_)
    {
        return RenderPass(uint32_t(lhs_) | uint32_t(rhs_));
    }

    constexpr RenderPass& operator&=(RenderPass& lhs_, RenderPass rhs_)
    {
        lhs_ = lhs_ & rhs_;
        return lhs_;
    }

    constexpr RenderPass& operator|=(RenderPass& lhs_, RenderPass rhs_)
    {
        lhs_ = lhs_ | rhs_;
        return lhs_;
    }

    constexpr bool Any(RenderPass flags_)
    {
        return flags_ != RenderPass::kNone;
    }
}

