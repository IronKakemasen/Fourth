#pragma once
#include "CommandContextToolLender.h"


class SwapChainContext;
class RenderContext;


struct CommandContext::ToolLender::AccessCommandQueueLicence
{
private:

	friend class SwapChainContext;
	explicit AccessCommandQueueLicence() = default;
};

struct CommandContext::ToolLender::UsesRuntimeCmdWrapperLicence
{
private:

	friend class RenderContext;
	explicit UsesRuntimeCmdWrapperLicence() = default;
};


