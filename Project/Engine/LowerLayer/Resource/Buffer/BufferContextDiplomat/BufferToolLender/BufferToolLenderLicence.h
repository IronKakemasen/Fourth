#pragma once
#include "BufferToolLender.h"
#include "../../../Mesh/MeshContext.h"

struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class MeshContext::ModelDataCreator;
	explicit BasicBufferManagementLicence() = default;
};

