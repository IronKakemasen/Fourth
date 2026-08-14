#pragma once
#include "../RenderContext.h"

class RenderContext::PassBehavior
{
public:
	PassBehavior(std::unique_ptr<RenderContext::PassDesc>&& desc_);
	virtual ~PassBehavior() = default;


protected:

	std::unique_ptr<RenderContext::PassDesc> desc;

};

