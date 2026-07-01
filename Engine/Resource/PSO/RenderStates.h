#pragma once
#include "RenderStateComponent.h"


struct RenderState
{
    RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kNormal;
    RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
    RenderStateComponent::FillMode fillMode = RenderStateComponent::FillMode::kSolid;
    RenderStateComponent::DepthWrite depthWrite = RenderStateComponent::DepthWrite::kEnable;
    RenderStateComponent::DepthTest depthTest = RenderStateComponent::DepthTest::kGreaterEqual;

};