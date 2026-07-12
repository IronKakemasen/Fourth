#pragma once
#include "../../RenderPass.h"

struct RenderPath::Pass::PassSettings
{
    RenderPassComponent::DepthTest depthTest;
    RenderPassComponent::DepthEnable depthEnable;
};