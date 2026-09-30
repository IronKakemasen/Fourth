#pragma once
#include "../PathBehavior.h"

class CreateSceneTexture:public RenderContext::PathBehavior
{
public:

	CreateSceneTexture(RenderContext::NexusFieldProof proof_, std::string const& name_);

	virtual void Run
	(
		std::unordered_map<uint64_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RenderStateComponent::FillMode const modelFillMode_,
		RenderContext::PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	)override;

private:

};

