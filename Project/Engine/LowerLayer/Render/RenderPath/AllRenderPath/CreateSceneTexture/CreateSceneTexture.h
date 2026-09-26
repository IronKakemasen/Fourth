#pragma once
#include "../PathBehavior.h"

class CreateSceneTexture:public RenderContext::PathBehavior
{
public:

	CreateSceneTexture(RenderContext::NexusFieldProof proof_, std::string const& name_);

	virtual void Update
	(
		[[maybe_unused]] std::vector<std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>>> const& modelContainer_,
		RuntimeWrapper& cmdWrapper_
	)override;

private:

};

