#include "PreCompileHeader.h"
#include "PassDesc.h"

namespace
{
	std::string const fileName = "PassDesc.cpp";
}

RenderContext::PassDesc::PassDesc
(
	std::string const name_,
	std::optional<std::pair<std::string, std::string >> const& ms_psFileName_,
	RenderPassState renderPassState_,
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& colorBuffersInfo_,
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& depthStencilBufferInfo_,
	std::vector <std::string> const& referenceBufferNames_
):
	renderPassState(renderPassState_) ,
	colorBuffersInfo(colorBuffersInfo_),
	depthStencilBufferInfo(depthStencilBufferInfo_),
	ms_psFileName(ms_psFileName_),
	referenceBufferNames(referenceBufferNames_), 
	passName(name_)
{

}

void RenderContext::PassDesc::DebugLog()const
{
	std::string log;

	log += "----- " + passName + " -----\n";
	log += "< ColorBuffersInfo(size = " + std::to_string(colorBuffersInfo.size()) + ")" + " >\n";
	int cnt{};
	for (auto const& info : colorBuffersInfo)
	{
		log += "Name: " + info.bufferName + " : [" + std::to_string(cnt) + "]\n";
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

	log += "< DepthSettings >";
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
		log += "\nDummy Value has been set\n";
	}

	log += "\n< ReferenceBuffers >\n\n";
	if (referenceBufferNames.size() == 0)
	{
		log += "NONE....\n";
	}
	else
	{
		log += "{ ";
		for (auto const bufferName : referenceBufferNames)
		{

			log += bufferName + " , ";
		}

		log += " }\n";
	}


	Logger::Log(log);
}