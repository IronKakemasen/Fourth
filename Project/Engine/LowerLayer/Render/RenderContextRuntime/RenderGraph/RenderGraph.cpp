#include "PreCompileHeader.h"
#include "RenderGraph.h"


RenderContext::RenderGraph::RenderGraph
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	Logger::Entry("RenderGraph: Constructor");

	Build
	(
		proof_,
		pathAssembler_,
		psoDispatcher_,
		passContainer_,
		rootSignatureContextDiplomat_,
		bufferContextDiplomat_,
		modelContextDiplomat_,
		pso_ContextDiplomat_,
		shaderContextDiplomat_
	);

	Logger::End("RenderGraph: Constructor");
}

