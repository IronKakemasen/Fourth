#pragma once
#include "WindowContextToolLender.h"

class SwapChainContext;
class DebugContext;


struct WindowContext::ToolLender::UsesHWNDLicence
{
private:

	friend class DebugContext;
	friend class SwapChainContext;
	explicit UsesHWNDLicence() = default;

};
