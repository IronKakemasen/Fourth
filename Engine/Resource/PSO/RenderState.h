#pragma once

namespace RenderStateComponent
{
    enum class BlendMode
    {
        kNormal,
        kAdd
    };

    enum class CullMode
    {
        kBack,
        kFront,
        kNone
    };
}


struct RenderState
{
    RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kNormal;
    RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
    bool depthWrite{};
    bool depthTest{};

    inline void Init
    (
        RenderStateComponent::BlendMode blendMode_,
        RenderStateComponent::CullMode cullMode_,
        bool depthWrite_,
        bool depthTest_
    )
    {
        blendMode = blendMode_;
        cullMode = cullMode_;
        depthWrite = depthWrite_;
        depthTest = depthTest_;
    }
};