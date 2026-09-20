#include "PreCompileHeader.h"
#include "StaticRenderGraph.h"


RenderContext::StaticRenderGraph::StaticRenderGraph
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
	Logger::Entry("StaticRenderGraph: Constructor");

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

	Logger::End("StaticRenderGraph: Constructor");
}

