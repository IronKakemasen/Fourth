#pragma once
#include "DescriptorHeapToolLender.h"

class SwapChainContext;
class BufferContext;
class RenderContext;

struct DescriptorHeapContext::ToolLender::BasicViewManagementLicence
{
private:

	friend class SwapChainContext;
	friend class BufferContext;
	explicit BasicViewManagementLicence() = default;
};


struct DescriptorHeapContext::ToolLender::UsesSrvDescriptorHeapLicence
{
private:

	friend class RenderContext;
	explicit UsesSrvDescriptorHeapLicence() = default;
};

