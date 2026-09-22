#include "PreCompileHeader.h"
#include "StaticRenderGraph.h"
#include "RenderGraphExecutor/PathOperator/PathOperator.h"
#include "RenderGraphExecutor/CommonCmdExecutor/CommonCmdExecutor.h"

namespace
{
	auto const fileName = "StaticRenderGraph.cpp";
}

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

	pathOperator.reset
	(
		new PathOperator(proof_, allPathPtr)
	);
	Logger::Log("Instantiate: PathOperator", fileName);
	
	commonCmdExecutor.reset(new CommonCmdExecutor(proof_, graphicsRootSig));
	Logger::Log("Instantiate: CommonCmdExecutor", fileName);



	Logger::End("StaticRenderGraph: Constructor");
}

RenderContext::StaticRenderGraph::~StaticRenderGraph()
{

}