#pragma once
#include "../../RenderPassBehavior.h"

struct RenderContext::PassBehavior::PassSettings
{
    RenderPassComponent::DepthTest depthTest;
    RenderPassComponent::DepthEnable depthEnable;
};