#pragma once
#include "../RenderPassComponent.h"
#include "../../RenderContext.h"

struct RenderContext::RenderPassState
{
	RenderPassState() = default;

	RenderPassState
	(
		RenderPassComponent::DepthTest depthTest_,
		RenderPassComponent::DepthEnable depthEnable_,
		INT depthBias_,
		FLOAT depthBiasClamp_,
		FLOAT slopeScaledDepthBias_
	):depthTest(depthTest_), depthEnable(depthEnable_), depthBias(depthBias_), depthBiasClamp(depthBiasClamp_), slopeScaledDepthBias(slopeScaledDepthBias_)
	{ }

	RenderPassComponent::DepthTest depthTest = RenderPassComponent::DepthTest::kGreaterEqual;
	RenderPassComponent::DepthEnable depthEnable = RenderPassComponent::DepthEnable::kEnable;
	INT depthBias = 0;
	FLOAT depthBiasClamp = 0.0f;
	FLOAT slopeScaledDepthBias = 0.0f;
};
