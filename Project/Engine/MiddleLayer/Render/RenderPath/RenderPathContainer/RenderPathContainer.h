#pragma once
#include "../../RenderContext.h"

class RenderContext::RenderPathContainer
{
public:

	RenderPathContainer(NexusFieldProof proof_);

	void Import(NexusFieldProof proof_ , std::unique_ptr<PathBehavior>&& path_);

private:

	std::vector<std::unique_ptr<PathBehavior>> container;
};

