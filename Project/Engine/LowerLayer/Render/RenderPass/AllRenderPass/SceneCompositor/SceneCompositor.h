#pragma once
#include "../RenderPassBehavior.h"


class SceneCompositor :public RenderContext::PassBehavior
{
public:

	SceneCompositor(RenderContext::NexusFieldProof proof_, std::unique_ptr<RenderContext::PassDesc>&& desc_);
	
	virtual void Update
	(
		[[maybe_unused]] std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	)override;


private:



};

