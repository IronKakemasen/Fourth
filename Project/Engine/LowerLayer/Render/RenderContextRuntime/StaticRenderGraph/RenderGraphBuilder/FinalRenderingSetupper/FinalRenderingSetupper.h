#pragma once
#include "../../StaticRenderGraph.h"


class RenderContext::StaticRenderGraph::FinalRenderingSetupper
{
	friend class StaticRenderGraph;


	RenderContext::StaticRenderGraph::BuildOutput::FinalRenderingSetupper Setup
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_,
		SwapChainContextDiplomat& swapChainContextDiplomat_
	);


};

