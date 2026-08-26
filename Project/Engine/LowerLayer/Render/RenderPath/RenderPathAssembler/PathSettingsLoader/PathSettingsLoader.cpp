#include "PreCompileHeader.h"
#include "PathSettingsLoader.h"
#include "../../../RenderPass/AllRenderPass/RenderPassTraits.h"

using namespace RenderPassTraits;

[[nodiscard]] std::vector<RenderContext::RenderPathAssembler::PassAndName> RenderContext::RenderPathAssembler::PathSettingsLoader::
ParseWhichPassUses(std::string const pathName_)
{

	//使用するPassを文字列で伝える
	std::vector<std::string> usesPassContainerString;
	std::vector<RenderPassComponent::Pass> usesPassContainer;
	std::vector<PassAndName> passType_string;

	usesPassContainerString = LoadData(pathName_);
	usesPassContainer = PassNamesToPassTypes(usesPassContainerString);
	
	for (size_t i = 0;i < usesPassContainerString.size();++i)
	{
		passType_string.emplace_back(std::make_pair(usesPassContainer[i], usesPassContainerString[i]));
	}

	return passType_string;
}


std::vector<std::string> RenderContext::RenderPathAssembler::PathSettingsLoader::LoadData(std::string const pathName_)
{
	Miyajison* miyajison = Miyajison::Get();
	static std::string const srcJsonFileName = "RenderPathSettings";
	static std::string const dataName = "UsePass";

	return 	miyajison->LoadData<std::vector<std::string>>(srcJsonFileName, { pathName_,dataName });

}

std::vector<RenderPassComponent::Pass> RenderContext::RenderPathAssembler::PathSettingsLoader::PassNamesToPassTypes(std::vector<std::string> const& passNames_)
{
	std::vector<RenderPassComponent::Pass> passTypes;

	for (auto const passName : passNames_)
	{
		passTypes.emplace_back(PassNameToPassType(passName));
	}

	return passTypes;
}
