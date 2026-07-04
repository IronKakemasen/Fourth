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
        kWireFrame = 2,
        kSolid = 3
    };

    enum class CullMode
    {
        kNone = 1,
        kFront = 2,
        kBack = 3
    };

    enum class DepthWrite
    {
        kDisable = 0, 
        kEnable = 1
    };

    enum class DepthTest
    {
        kLessEqual = 4,
        kGreaterEqual = 7
    };

    //モデル一つにつき１定義のみ
    struct Uniqued
    {
        RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
        RenderStateComponent::DepthWrite depthWrite = RenderStateComponent::DepthWrite::kEnable;
        RenderStateComponent::DepthTest depthTest = RenderStateComponent::DepthTest::kGreaterEqual;
    };

    //複数定義可能
    struct Flexible
    {
        RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kOpaque;
    };

}

