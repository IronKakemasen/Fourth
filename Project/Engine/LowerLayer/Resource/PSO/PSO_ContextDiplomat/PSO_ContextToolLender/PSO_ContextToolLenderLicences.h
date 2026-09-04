#pragma once
#include "PSO_ContextToolLender.h"

class RenderContext;

struct PSO_Context::ToolLender::UsesPSO_CreatorLicence
{
private:

	friend class RenderContext;
	explicit UsesPSO_CreatorLicence() = default;

};

