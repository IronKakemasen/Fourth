#include "PreCompileHeader.h"
#include "PathOperator.h"
#include "../../../../RenderPath/AllRenderPath/PathBehavior.h"


//外部
#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"




RenderContext::StaticRenderGraph::PathOperator::PathOperator
(
	NexusFieldProof proof_,
	std::vector<PathBehavior*>& allPathPtr_
):allPathPtr(allPathPtr_)
{

}


void RenderContext::StaticRenderGraph::PathOperator::Run
(
	UINT const frameIndex_,
	ModelContextDiplomat& modelContextDiplomat_,
	RuntimeWrapper& runtimeWrapper_
)
{
	for (auto* path : allPathPtr)
	{
		//path->Update()
	}
}
