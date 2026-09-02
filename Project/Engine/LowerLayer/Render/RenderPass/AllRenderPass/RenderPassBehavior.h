#pragma once
#include "../../RenderContext.h"
#include "../PassDesc/PassDesc.h"

#include "../../../Core/Command/CommandContext.h"

class Model;

class RenderContext::PassBehavior
{
public:

	PassBehavior(NexusFieldProof proof_, const PassDesc& desc_,RenderPassComponent::Pass pass_);
	virtual ~PassBehavior() = default;

	PassDesc const& WatchDesc() const { return desc; }

	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	) = 0;

protected:

	//PSO特定のためにもっておく。PassDescの簡略キーみたいな。
	RenderPassComponent::Pass pass;

	PassDesc desc;
};

