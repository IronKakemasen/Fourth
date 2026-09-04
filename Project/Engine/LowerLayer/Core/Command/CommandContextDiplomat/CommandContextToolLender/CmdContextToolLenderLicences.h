#pragma once
#include "CommandContextToolLender.h"


class SwapChainContext;

struct CommandContext::ToolLender::AccessCommandQueueLicence
{
private:

	friend class SwapChainContext;
	explicit AccessCommandQueueLicence() = default;
};
