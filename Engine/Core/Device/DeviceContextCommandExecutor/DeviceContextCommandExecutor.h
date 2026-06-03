#pragma once
#include "../DeviceContext.h"

//DeviceContextから都度deviceをリクエストしてコマンド実行するクラス。
class DeviceContext::CommandExecutor
{
public:

	//DeviceContextのみ生成可能
	struct InstanceKey;

	CommandExecutor(InstanceKey instanceKey_, std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_);

private:

	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> deviceGetter;

};

//生成できるのはDeviceContextのみ
struct DeviceContext::CommandExecutor::InstanceKey
{
private:

	friend class DeviceContext;
	explicit InstanceKey() = default;
};




