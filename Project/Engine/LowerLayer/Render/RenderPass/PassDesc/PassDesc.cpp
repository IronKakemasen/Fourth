#include "PreCompileHeader.h"
#include "PassDesc.h"

namespace
{
	std::string const fileName = "PassDesc.cpp";
}

RenderContext::PassDesc::PassDesc
(
	std::string name_,
	std::optional<std::pair<std::string, std::string >> ms_psFileName_,
	RenderPassState renderPassState_,
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
):renderPassState(renderPassState_) , colorBuffersInfo(colorBuffersInfo_), depthStencilBufferInfo(depthStencilBufferInfo_), ms_psFileName(ms_psFileName_),passName(name_)
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
std::string const RenderContext::PassDesc::WatchName()const
{
	return passName;
}

void RenderContext::PassDesc::DebugLog()const
{
	std::string log;

	log += "----- " + passName + " -----\n";
	log += "< ColorBuffersInfo(size = " + std::to_string(colorBuffersInfo.size()) + ")" + " >\n";
	int cnt{};
	for (auto const& info : colorBuffersInfo)
	{
		log += "Name: " + info.bufferName + "[" + std::to_string(cnt) + "]\n";
		log += "BufferUnique: " + std::to_string((UINT)info.bufferID) + "\n";
		log += "Format: " + std::to_string((UINT)info.format) + "\n";
		log += "Width x Height: " + std::to_string(info.width) + " x " + std::to_string(info.height) + "\n";
		log += "NumBuffer: " + std::to_string((UINT)info.numBuffer) + "\n";
		log += "BlendMode: " + RenderStateComponent::BlendModeToString(info.blendMode);
		log += "\n\n";
	}

	log += "< DepthStencilBufferInfo >\n";

	if (depthStencilBufferInfo.has_value())
	{
		auto const& info = *depthStencilBufferInfo;

		log += "Name: " + info.bufferName + "\n";
		log += "BufferUnique: " + std::to_string((UINT)info.bufferID) + "\n";
		log += "Format: " + std::to_string((UINT)info.dsvFormat) + "\n";
		log += "Width x Height: " + std::to_string(info.width) + " x " + std::to_string(info.height) + "\n";
		log += "NumBuffer: " + std::to_string((UINT)info.numBuffer);
		log += "\n\n";
	}
	else
	{
		log += "None";
		log += "\n\n";

	}

	log += "< RenderState >";
	if (depthStencilBufferInfo.has_value())
	{
		log += "\nDepthEnable: " + std::to_string((int)renderPassState.depthEnable);
		log += "\nDepthTest: " + RenderPassComponent::DepthTestString(renderPassState.depthTest);
		log += "\nDepthBias: " + std::to_string((int)renderPassState.depthBias);
		log += "\nDepthBiasClamp: " + std::to_string((float)renderPassState.depthBiasClamp);
		log += "\nSlopeScaledDepthBias: " + std::to_string((float)renderPassState.slopeScaledDepthBias);
		log += "\n";
	}
	else
	{
		log += "\nDammy Value has been set\n";
	}

	Logger::Log(log);
}