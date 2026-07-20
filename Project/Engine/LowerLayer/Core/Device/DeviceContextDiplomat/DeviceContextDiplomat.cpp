#include "PreCompileHeader.h"
#include "DeviceContextDiplomat.h"

#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

namespace
{
	auto const fileName = "CommandContextDiplomat.cpp";
}

DeviceContextDiplomat::DeviceContextDiplomat
(
	DeviceContext::InstanceKey key_,
	std::unique_ptr<DeviceContext::CommandProvider>&& cmdProvider_,
	std::unique_ptr<DeviceContext::CommandExecutor>&& cmdExecutor_
)
{
	std::get<std::unique_ptr<DeviceContext::CommandProvider>>(tools) = std::move(cmdProvider_);
	std::get<std::unique_ptr<DeviceContext::CommandExecutor>>(tools) = std::move(cmdExecutor_);

}
