#pragma once
#include "../RenderPassBehavior.h"

class SceneOpaque :public RenderContext::PassBehavior
{
public:

	SceneOpaque(RenderContext::NexusFieldProof proof_, std::unique_ptr<RenderContext::PassDesc>&& desc_);

	virtual void Update
	(
		[[maybe_unused]] std::pair<RenderStateKey, std::vector<Model*>> const& modelContainer_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	)override;

private:

};

