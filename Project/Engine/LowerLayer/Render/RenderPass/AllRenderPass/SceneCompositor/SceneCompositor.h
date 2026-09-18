#pragma once
#include "../RenderPassBehavior.h"


class SceneCompositor :public RenderContext::PassBehavior
{
public:

	SceneCompositor(RenderContext::NexusFieldProof proof_, std::unique_ptr<RenderContext::PassDesc>&& desc_);
	
	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	)override;


private:



};

