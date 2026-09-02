#pragma once
#include "../RenderPassBehavior.h"

class SceneTextureCreatorOpaque :public RenderContext::PassBehavior
{
public:

	SceneTextureCreatorOpaque(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_);

	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	)override;

private:

};

