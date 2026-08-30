#pragma once

namespace RenderStateComponent
{
    //追加したら下の変換関数もね
    enum class BlendMode
    {
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

        
        ErrorMessageOutput::Assert::DetectError(blendMode != BlendMode::kCount, "ブレンドモードの文字変換失敗", "RenderStateComponent.h");
        
        return blendMode;
    }

    inline const std::string BlendModeToString(BlendMode mode_)
    {
        std::string blendMode = "";

        if      (mode_ == BlendMode::kOpaque)            blendMode = "kOpaque";
        else if (mode_ == BlendMode::kAlphaBlend)        blendMode = "kAlphaBlend";
        else if (mode_ == BlendMode::kAdditive)          blendMode = "kAdditive";
        else if (mode_ == BlendMode::kDependsModel)      blendMode = "kDependsModel";

        ErrorMessageOutput::Assert::DetectError(blendMode.size()> 0 , "ブレンドモードの文字変換失敗", "RenderStateComponent.h");

        return blendMode;
    }

    inline D3D12_FILL_MODE Convert(FillMode fillMode_)
    {
        return (fillMode_ == FillMode::kSolid) ? D3D12_FILL_MODE_SOLID : D3D12_FILL_MODE_WIREFRAME;
    }

    inline D3D12_CULL_MODE Convert(CullMode cullMode_)
    {
        D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK;

        if      (cullMode_ == CullMode::kFront) cullMode = D3D12_CULL_MODE_FRONT;
        else if (cullMode_ == CullMode::kNone)  cullMode = D3D12_CULL_MODE_NONE;

        return cullMode;
    }

}

