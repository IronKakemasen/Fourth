#pragma once
#include "../CommandContext.h"


//コマンドコンテキストの外交官クラス
class CommandContextDiplomat
{
public:
	CommandContextDiplomat
	(
		CommandContext::InstanceKey key_,
		std::unique_ptr<CommandContext::CommandProvider>&& cmdProvider_,
		std::unique_ptr<CommandContext::ToolLender>&& toolLender_
	);

	template<typename ToolType>
	ToolType* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:
	//提供するツールのテーブル
	std::tuple<std::unique_ptr<CommandContext::CommandProvider>, std::unique_ptr<CommandContext::ToolLender>> tools;

};

