#pragma once
#include "SwapChainContextToolLender.h"

class RenderContext;

struct SwapChainContext::ToolLender::UsesSwapChainBufferLicence
{
private:

	friend class RenderContext;
	explicit UsesSwapChainBufferLicence() = default;
};