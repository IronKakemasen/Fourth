#pragma once
#include "../../RenderContext.h"


class DescriptorHeapContextDiplomat;
class CommandContextDiplomat;
class SceneContextDiplomat;


class RenderContext::ExecutionAgent
{
public:

	ExecutionAgent
	(
		NexusFieldProof proof_,
		StaticRenderGraph& staticRenderGraph_
	);

	void RenderGraphRun
	(
		NexusFieldProof proof_,
		UINT const frameIndex_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		SceneContextDiplomat& sceneContextDiplomat_,
		SwapChainContextDiplomat& swapChainContextDiplomat_
	);


private:

	StaticRenderGraph& staticRenderGraph;
};

