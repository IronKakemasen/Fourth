#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::PathOperator
{
public:

	PathOperator
	(
		NexusFieldProof proof_,
		std::vector<PathBehavior*>& allPathPtr_
	);


private:
	std::vector<PathBehavior*>& allPathPtr;

};

