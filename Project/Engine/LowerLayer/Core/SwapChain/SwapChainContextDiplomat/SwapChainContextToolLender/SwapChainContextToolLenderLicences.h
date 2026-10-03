#pragma once
#include "SwapChainContextToolLender.h"

class RenderContext;

struct SwapChainContext::ToolLender::UsesSwapChainBufferLicence
{
	friend class RenderContext;
	explicit UsesSwapChainBufferLicence() = default;
};