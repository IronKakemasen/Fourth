#pragma once
#include "BufferContextCmdProvider.h"

class ModelContext;

struct BufferContext::CmdProvider::UsesCBufferCreatorLicence
{
private:

	friend class ModelContext;
	explicit UsesCBufferCreatorLicence() = default;
};


