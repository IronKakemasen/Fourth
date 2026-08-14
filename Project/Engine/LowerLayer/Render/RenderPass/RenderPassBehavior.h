#pragma once
#include "../RenderContext.h"
#include "PassDesc/PassDesc.h"

class RenderContext::PassBehavior
{
public:
	PassBehavior(Local_CreateRenderPassLicence licence_ , const RenderContext::PassDesc& desc_);
	virtual ~PassBehavior() = default;


protected:

	RenderContext::PassDesc desc;

};

