#pragma once
#include "../RenderContext.h"
#include "PassDesc/PassDesc.h"

class RenderContext::PassBehavior
{
public:
	PassBehavior(NexusFieldProof proof_, const RenderContext::PassDesc& desc_);
	virtual ~PassBehavior() = default;


protected:

	RenderContext::PassDesc desc;

};

