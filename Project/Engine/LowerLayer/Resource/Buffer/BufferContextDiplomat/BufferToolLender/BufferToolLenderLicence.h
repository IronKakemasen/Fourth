#pragma once
#include "BufferToolLender.h"
#include "../../../Model/ModelContext.h"
#include "../../../../Render/RenderContext.h"

struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext::ModelDataCreator;
	friend class RenderContext::RenderPassCreator;

	explicit BasicBufferManagementLicence() = default;
};

