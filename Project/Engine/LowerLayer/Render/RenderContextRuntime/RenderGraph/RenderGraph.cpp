#include "PreCompileHeader.h"
#include "RenderGraph.h"


RenderContext::RenderGraph::RenderGraph
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_
)
{
	Logger::Entry("RenderGraph: Constructor");

	Init
	(
		proof_,
		pathAssembler_,
		psoDispatcher_,
		rootSignatureContextDiplomat_,
		bufferContextDiplomat_,
		modelContextDiplomat_
	);

	Logger::End("RenderGraph: Constructor");
}

