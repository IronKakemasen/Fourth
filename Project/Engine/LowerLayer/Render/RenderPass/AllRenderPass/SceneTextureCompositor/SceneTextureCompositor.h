#pragma once
#include "../RenderPassBehavior.h"


class SceneTextureCompositor :public RenderContext::PassBehavior
{
public:

	SceneTextureCompositor(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_);
	
	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	)override;


private:



};

