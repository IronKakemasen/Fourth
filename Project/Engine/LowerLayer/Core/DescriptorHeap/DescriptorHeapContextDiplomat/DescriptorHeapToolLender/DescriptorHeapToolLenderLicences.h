#pragma once
#include "DescriptorHeapToolLender.h"

class SwapChainContext;
class BufferContext;
class RenderContext;
class DebugContext;

struct DescriptorHeapContext::ToolLender::BasicViewManagementLicence
{
private:

	friend class SwapChainContext;
	friend class BufferContext;
	friend class DebugContext;

	explicit BasicViewManagementLicence() = default;
};


struct DescriptorHeapContext::ToolLender::UsesSrvDescriptorHeapLicence
{
private:

	friend class RenderContext;
	friend class DebugContext;

	explicit UsesSrvDescriptorHeapLicence() = default;
};

