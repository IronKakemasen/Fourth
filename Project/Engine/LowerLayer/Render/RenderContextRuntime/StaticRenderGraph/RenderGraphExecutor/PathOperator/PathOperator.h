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

	//全pathの更新処理をぶん回す
	void Run
	(
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		RuntimeWrapper& runtimeWrapper_
	);

private:
	std::vector<PathBehavior*>& allPathPtr;

};

