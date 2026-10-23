#include "PreCompileHeader.h"
#include "RenderContextExecutionAgent.h"
#include "../../RenderContextRuntime/StaticRenderGraph/StaticRenderGraph.h"


RenderContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	StaticRenderGraph& staticRenderGraph_
):staticRenderGraph(staticRenderGraph_)
{

}

void RenderContext::ExecutionAgent::RenderGraphRun
(
	NexusFieldProof proof_,
	UINT const frameIndex_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
	CommandContextDiplomat& commandContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	SceneContextDiplomat& sceneContextDiplomat_,
	SwapChainContextDiplomat& swapChainContextDiplomat_
)
{
	staticRenderGraph.Run
	(
		proof_,
		AgentKey{},
		frameIndex_,
		descriptorHeapContextDiplomat_,
		commandContextDiplomat_,
		bufferContextDiplomat_,
		sceneContextDiplomat_,
		swapChainContextDiplomat_
	);

}
