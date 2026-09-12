#pragma once
#include "BufferToolLender.h"

class ModelContext;
class RenderContext;
class TextureContext;

struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext;
	friend class RenderContext;
	friend class TextureContext;

	explicit BasicBufferManagementLicence() = default;
};

