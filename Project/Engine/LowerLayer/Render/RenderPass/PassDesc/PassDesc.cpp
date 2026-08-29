#include "PreCompileHeader.h"
#include "PassDesc.h"

namespace
{
	std::string const fileName = "PassDesc.cpp";
}

RenderContext::PassDesc::PassDesc
(
	std::optional<std::pair<std::string, std::string >> ms_psFileName_,
	RenderPassState renderPassState_,
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):renderPassState(renderPassState_) , colorBuffersInfo(colorBuffersInfo_), depthStencilBufferInfo(depthStencilBufferInfo_), ms_psFileName(ms_psFileName_)
{

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

std::optional<std::pair<std::string, std::string >> const& RenderContext::PassDesc::WatchMs_PsFileName()const
{
	return ms_psFileName;
}

RenderContext::RenderPassState const& RenderContext::PassDesc::WatchRenderPassState()const
{
	return renderPassState;
}

