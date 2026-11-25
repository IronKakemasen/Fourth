#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::FinalRenderer
{
public:

	FinalRenderer
	(
		NexusFieldProof proof_,
		ID3D12PipelineState* finalRenderingPso_,
		BufferUniqueID finalRefBufferID
	);

	void RenderBackBuffer
	(
		UINT const frameIndex_,
		RuntimeWrapper& runtimeWrapper_,
		SwapChainContextDiplomat& swapChainContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		DebugContextDiplomat& debugContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_
	);


private:
	//最終描画用PSO
	ID3D12PipelineState* finalRenderingPso;
	//最終参照テクスチャsrvHeapIndex
	BufferUniqueID finalRefBufferID;
	

};

