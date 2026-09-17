#pragma once
#include "../RenderPassBehavior.h"

class SceneOpaque :public RenderContext::PassBehavior
{
public:

	SceneOpaque(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_);

	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	)override;

private:

};

