#include "PreCompileHeader.h"
#include "PassDescBehavior.h"

namespace
{
	std::string const fileName = "AddDepthStencilBufferInfo.cpp";
}

RenderContext::PassDescBehavior::PassDescBehavior
(
	RenderPassComponent::DepthTest depthTest_,
	RenderPassComponent::DepthEnable depthEnable_,
	std::vector<RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):colorBuffersInfo(colorBuffersInfo_), depthStencilBufferInfo(depthStencilBufferInfo_), depthTest(depthTest_), depthEnable(depthEnable_)
{

}





