#pragma once
#include "../RenderPassCreator.h"
#include "../../PassDesc/PassRequiredInfo.h"


class RenderContext::RenderPassCreator::PassDescAssembler
{
	friend class RenderPassCreator;

	static [[nodiscard]] PassRequiredInfo LoadPassSettings(std::string const passName_);

	static std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> ParseColorBufferInfo
	(
		std::string const passName_,
		std::string const jsonFileName_
	);

	static std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> ParseDepthStencilBufferInfo
	(
		std::string const passName_,
		std::string const jsonFileName_
	);


};

