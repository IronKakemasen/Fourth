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
}

