#pragma once
#include "BufferToolLender.h"
#include "../../../Model/ModelContext.h"


struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext::ModelDataCreator;

	explicit BasicBufferManagementLicence() = default;
};

