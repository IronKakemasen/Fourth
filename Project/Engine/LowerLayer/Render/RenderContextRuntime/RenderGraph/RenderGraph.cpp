#include "PreCompileHeader.h"
#include "RenderGraph.h"


RenderContext::RenderGraph::RenderGraph
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	Logger::Entry("RenderGraph: Constructor");

	Init
	(
		proof_,
		pathAssembler_,
		rootSignatureContextDiplomat_,
		bufferContextDiplomat_
	);

	Logger::End("RenderGraph: Constructor");
}

