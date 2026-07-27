#pragma once
#include "BufferToolLender.h"
#include "../../../Mesh/ModelContext.h"

struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext::ModelDataCreator;
	explicit BasicBufferManagementLicence() = default;
};

