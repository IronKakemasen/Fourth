#pragma once

#include "../PassDescBehavior.h"

class SceneTextureCreatorDesc final : public RenderContext::PassDescBehavior
{
public:

	SceneTextureCreatorDesc
	(
		RenderPassComponent::DepthTest depthTest_,
		RenderPassComponent::DepthEnable depthEnable_,
		std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
		std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
	);



private:

};