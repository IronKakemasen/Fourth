#pragma once
#include "PSO_ContextToolLender.h"
#include "../../../../Render/RenderContext.h"


struct PSO_Context::ToolLender::UsesPSO_CreatorLicence
{
private:

	friend class RenderContext::RenderGraph;
	explicit UsesPSO_CreatorLicence() = default;

};

