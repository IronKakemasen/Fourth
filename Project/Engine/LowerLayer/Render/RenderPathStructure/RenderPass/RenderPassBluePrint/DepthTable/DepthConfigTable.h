#pragma once
#include "../RenderPassBluePrint.h"

struct RenderPassBluePrint::DepthTable
{
	struct DepthConfig
	{
		RenderPassComponent::DepthTest depthTest;
		RenderPassComponent::DepthEnable depthEnable;
	};

	DepthConfig DepthConfigTable(RenderPassComponent::Pass pass_);
};

