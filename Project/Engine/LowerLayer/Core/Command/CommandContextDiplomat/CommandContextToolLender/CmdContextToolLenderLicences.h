#pragma once
#include "CommandContextToolLender.h"


class SwapChainContext;
class RenderContext;
class DebugContext;

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


struct CommandContext::ToolLender::AccessCommandListLicence
{
private:

	friend class DebugContext;
	explicit AccessCommandListLicence() = default;
};



