#pragma once
#include "../../RenderContext.h"
#include "../PassDesc/PassDesc.h"


class RenderContext::PassBehavior
{
public:
	PassBehavior(NexusFieldProof proof_, const PassDesc& desc_,RenderPassComponent::Pass pass_);
	virtual ~PassBehavior() = default;

	PassDesc const& WatchDesc() const { return desc; }


protected:

	//PSO特定のためにもっておく。PassDescの簡略キーみたいな。
	RenderPassComponent::Pass pass;

	PassDesc desc;
};

