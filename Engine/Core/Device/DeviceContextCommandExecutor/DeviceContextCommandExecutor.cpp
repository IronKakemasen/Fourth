#include "PreCompileHedder.h"
#include "DeviceContextCommandExecutor.h"


DeviceContext::CommandExecutor::CommandExecutor(InstanceKey instanceKey_, std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_)
{
	deviceGetter = func_;
}
