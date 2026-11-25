#pragma once
#include "DeviceContextCommandExecutor.h"

class CommandContext;
class DebugContext;

struct DeviceContext::CommandExecutor::CommandContextProof
{
private:

	friend class CommandContext;
	explicit CommandContextProof() = default;
};

struct DeviceContext::CommandExecutor::DebugContextProof
{
private:

	friend class DebugContext;
	explicit DebugContextProof() = default;

};
