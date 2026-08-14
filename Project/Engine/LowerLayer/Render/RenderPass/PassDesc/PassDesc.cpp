#include "PreCompileHeader.h"
#include "PassDesc.h"

namespace
{
	std::string const fileName = "PassDesc.cpp";
}

RenderContext::PassDesc::PassDesc
(
	RenderPassComponent::DepthTest depthTest_,
	RenderPassComponent::DepthEnable depthEnable_,
	std::vector<RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):colorBuffersInfo(colorBuffersInfo_), depthStencilBufferInfo(depthStencilBufferInfo_), depthTest(depthTest_), depthEnable(depthEnable_)
{

}





