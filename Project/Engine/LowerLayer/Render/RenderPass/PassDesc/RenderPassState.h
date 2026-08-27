#pragma once
#include "../RenderPassComponent.h"
#include "../../RenderContext.h"

struct RenderContext::RenderPassState
{
	RenderPassComponent::DepthTest depthTest = RenderPassComponent::DepthTest::kGreaterEqual;
	RenderPassComponent::DepthEnable depthEnable = RenderPassComponent::DepthEnable::kEnable;

};
