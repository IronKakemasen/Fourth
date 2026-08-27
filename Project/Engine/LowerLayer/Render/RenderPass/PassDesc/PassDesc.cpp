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
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):colorBuffersInfo(colorBuffersInfo_), depthStencilBufferInfo(depthStencilBufferInfo_)
{
	renderPassState.depthTest = depthTest_;
	renderPassState.depthEnable = depthEnable_;
}

bool RenderContext::PassDesc::DoesDepthStencilBufferInfoContains()const
{
	return depthStencilBufferInfo.has_value() ? 1 : 0;
}


void RenderContext::PassDesc::SetColorBufferUniqueID(BufferUniqueID id_, size_t index_)
{
	colorBuffersInfo[index_].bufferID = id_;
}

void RenderContext::PassDesc::SetDepthStencilBufferUniqueID(BufferUniqueID id_)
{
	depthStencilBufferInfo->bufferID = id_;
}

std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& RenderContext::PassDesc::WatchColorBuffersInfo()const
{
	return colorBuffersInfo;
}

std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& RenderContext::PassDesc::WatchDepthStencilBufferInfo()const
{
	return depthStencilBufferInfo;
}

RenderContext::RenderPassState const& RenderContext::PassDesc::WatchRenderPassState()const
{
	return renderPassState;
}

