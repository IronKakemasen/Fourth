#pragma once
#include "BufferContextCmdProvider.h"

class ModelContext;
class TextureContext;
class RenderContext;

struct BufferContext::CmdProvider::UsesCBufferCreatorLicence
{
private:

	friend class ModelContext;
	friend class TextureContext;
	friend class RenderContext;

	explicit UsesCBufferCreatorLicence() = default;
};


