#pragma once
#include "WindowContextToolLender.h"

class SwapChainContext;

struct WindowContext::ToolLender::UsesHWNDLicence
{
private:
	friend class SwapChainContext;
	explicit UsesHWNDLicence() = default;

};
