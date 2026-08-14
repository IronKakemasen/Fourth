#include "SceneTextureCreatorDesc.h"



SceneTextureCreatorDesc::SceneTextureCreatorDesc
(
	RenderPassComponent::DepthTest depthTest_,
	RenderPassComponent::DepthEnable depthEnable_,
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):RenderContext::PassDescBehavior(depthTest_, depthEnable_, colorBuffersInfo_, depthStencilBufferInfo_)
{

}
