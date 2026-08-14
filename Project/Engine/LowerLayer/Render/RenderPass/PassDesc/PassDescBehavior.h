#pragma once
#include "../BufferRequiredInfo.h"
#include "../RenderPassComponent.h"


class RenderContext::PassDescBehavior
{
public:

	PassDescBehavior
	(
		RenderPassComponent::DepthTest depthTest_,
		RenderPassComponent::DepthEnable depthEnable_,
		std::vector<RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
		std::optional<RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
	);


protected:

	RenderPassComponent::DepthTest depthTest;
	RenderPassComponent::DepthEnable depthEnable;

	std::vector<RequiredBufferInfo::ColorBuffer> colorBuffersInfo;
	std::optional<RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;


};

