#include "PreCompileHeader.h"
#include "RenderGraph.h"


RenderContext::RenderGraph::RenderGraph
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	PSO_PoolDispatcher& psoDispatcher_,
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
		renderPassCreator_,
		passContainer_,
		rootSignatureContextDiplomat_,
		bufferContextDiplomat_,
		modelContextDiplomat_,
		pso_ContextDiplomat_,
		shaderContextDiplomat_
	);

	Logger::End("RenderGraph: Constructor");
}

