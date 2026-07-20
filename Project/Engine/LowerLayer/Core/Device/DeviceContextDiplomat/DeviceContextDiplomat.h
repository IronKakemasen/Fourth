#pragma once
#include "../DeviceContext.h"

class DeviceContextDiplomat
{
public:
	DeviceContextDiplomat
	(
		DeviceContext::InstanceKey key_,
		std::unique_ptr<DeviceContext::CommandProvider>&& cmdProvider_,
		std::unique_ptr<DeviceContext::CommandExecutor>&& cmdExecutor_
	);

	template<typename ToolType>
	ToolType* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:
	//提供するツールのテーブル
	std::tuple<std::unique_ptr<DeviceContext::CommandProvider>, std::unique_ptr<DeviceContext::CommandExecutor>> tools;


};
