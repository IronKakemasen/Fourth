#pragma once
#include "../RenderPassCreator.h"
#include "../../PassDesc/PassDesc.h"


class RenderContext::RenderPassCreator::PassSettingsLoader
{
	friend class RenderPassCreator;

	static [[nodiscard]] PassDesc Load(std::string const passName_);


	//以下ヘルパー
private:
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

	static RenderPassState ParseRenderPassState
	(
		std::string const passName_,
		std::string const jsonFileName_
	);

	static std::optional<std::pair<std::string, std::string >> ParseShaderFile
	(
		std::string const passName_,
		std::string const jsonFileName_
	);

};

