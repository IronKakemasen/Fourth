#pragma once
#include "BufferContextCmdProvider.h"
#include "../../../Model/ModelContext.h"


struct BufferContext::CmdProvider::UsesCBufferCreatorLicence
{
private:

	friend class ModelContext::ModelDataCreator;
	explicit UsesCBufferCreatorLicence() = default;
};


