#pragma once
#include "../RenderPassComponent.h"
#include "../../RenderContext.h"

struct RenderContext::RenderPassState
{
	RenderPassState() = default;

	RenderPassState
	(
		RenderPassComponent::DepthTest depthTest_,
		RenderPassComponent::DepthEnable depthEnable_
	):depthTest(depthTest_), depthEnable(depthEnable_)
	{ }

	RenderPassComponent::DepthTest depthTest = RenderPassComponent::DepthTest::kGreaterEqual;
	RenderPassComponent::DepthEnable depthEnable = RenderPassComponent::DepthEnable::kEnable;

};
