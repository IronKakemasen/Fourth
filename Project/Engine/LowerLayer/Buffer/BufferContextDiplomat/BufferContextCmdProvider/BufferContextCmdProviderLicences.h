#pragma once
#include "BufferContextCmdProvider.h"

class ModelContext;
class TextureContext;

struct BufferContext::CmdProvider::UsesCBufferCreatorLicence
{
private:

	friend class ModelContext;
	friend class TextureContext;

	explicit UsesCBufferCreatorLicence() = default;
};


