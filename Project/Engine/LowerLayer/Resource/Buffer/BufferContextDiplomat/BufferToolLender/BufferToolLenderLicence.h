#pragma once
#include "BufferToolLender.h"

class ModelContext;
class RenderContext;

struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext;
	friend class RenderContext;

	explicit BasicBufferManagementLicence() = default;
};

