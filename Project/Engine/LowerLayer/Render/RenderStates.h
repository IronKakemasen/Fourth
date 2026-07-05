#pragma once
#include "RenderPathStructure/RenderStateComponent.h"


struct RenderState
{
    inline RenderState
    (
        RenderStateComponent::Uniqued uniqued_,
        const std::vector<RenderStateComponent::Flexible>& flexible_
    ): uniqued(uniqued_) , flexible(flexible_)
    {
        ErrorMessageOutput::Assert::DetectError(flexible_.size() > 0, "flexible_が未定義", "RenderState.h");
    }

private:

    //モデルのレンダーステートをもとにPSOを構築するクラスをフレンドクラスに
    //friend class 

    RenderStateComponent::Uniqued uniqued;
    std::vector<RenderStateComponent::Flexible> flexible;
};

