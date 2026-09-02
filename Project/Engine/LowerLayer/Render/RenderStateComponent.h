#pragma once

namespace RenderStateComponent
{
    //追加したら下の変換関数もね
    enum class BlendMode
    {
        ///RenderPass専用！！！
        kOffScreen,

        kOpaque,
        kAlphaBlend,
        kAdditive
        ,kCount,

        ///RenderPass専用！！！
        kDependsModel,
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

    inline BlendMode const BlendModeToEnum(std::string blendModeString_)
    {
        BlendMode blendMode = BlendMode::kCount;

        if      (blendModeString_ == "kOpaque")         blendMode = BlendMode::kOpaque;
        else if (blendModeString_ == "kAlphaBlend")     blendMode = BlendMode::kAlphaBlend;
        else if (blendModeString_ == "kAdditive")       blendMode = BlendMode::kAdditive;
        else if (blendModeString_ == "kDependsModel")   blendMode = BlendMode::kDependsModel;

        
        ErrorMessageOutput::Assert::DetectError
        (
            blendMode != BlendMode::kCount, 
            blendModeString_ + "この文字列は対応してない(BlendMode)",
            "RenderStateComponent.h"
        );
        
        return blendMode;
    }

    inline const std::string BlendModeToString(BlendMode mode_)
    {
        std::string blendModeString = "";

        if      (mode_ == BlendMode::kOpaque)           blendModeString = "kOpaque";
        else if (mode_ == BlendMode::kAlphaBlend)       blendModeString = "kAlphaBlend";
        else if (mode_ == BlendMode::kAdditive)         blendModeString = "kAdditive";
        else if (mode_ == BlendMode::kDependsModel)     blendModeString = "kDependsModel";

        ErrorMessageOutput::Assert::DetectError
        (
            mode_ != BlendMode::kCount,
            "そいつぁ指定できねぇぜ(BlendMode)", 
            "RenderStateComponent.h"
        );

        return blendModeString;
    }

    inline D3D12_FILL_MODE Convert(FillMode fillMode_)
    {
        return (fillMode_ == FillMode::kSolid) ? D3D12_FILL_MODE_SOLID : D3D12_FILL_MODE_WIREFRAME;
    }

    inline const std::string FillModeToString(FillMode mode_)
    {
        std::string fillModeString = "";

        if (mode_ == FillMode::kSolid)              fillModeString = "kSolid";
        else if (mode_ == FillMode::kWireFrame)     fillModeString = "kWireFrame";

        ErrorMessageOutput::Assert::DetectError
        (
            mode_ != FillMode::kCount,
            "そいつぁ指定できねぇぜ(FillMode)",
            "RenderStateComponent.h"
        );

        return fillModeString;
    }


    inline D3D12_CULL_MODE Convert(CullMode cullMode_)
    {
        D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK;

        if      (cullMode_ == CullMode::kFront) cullMode = D3D12_CULL_MODE_FRONT;
        else if (cullMode_ == CullMode::kNone)  cullMode = D3D12_CULL_MODE_NONE;

        return cullMode;
    }



}

