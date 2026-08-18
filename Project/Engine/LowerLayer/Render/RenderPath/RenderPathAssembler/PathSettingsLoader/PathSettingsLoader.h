#pragma once
#include "../RenderPathAssembler.h"

class RenderContext::RenderPathAssembler::PathSettingsLoader
{
	friend class RenderPathAssembler;

	///本丸
	[[nodiscard]] static std::vector<PassAndName> ParseWhichPassUses(std::string const pathName_);

	//Pathの名前からそのPathが使用するPassの名前をjsonファイルから読み込む
	static std::vector<std::string> LoadData(std::string const pathName_);
	//パスの名前から列挙型へ変換
	static std::vector<RenderPassComponent::Pass> PassNamesToPassTypes(std::vector<std::string> const& passNames_);
};

