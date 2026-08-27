#include "RenderContext.h"

#include "RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "RenderPass/AllRenderPass/RenderPassBehavior.h"

#include "RenderPath/RenderPathAssembler/RenderPathAssembler.h"
#include "RenderPath/RenderPathContainer/RenderPathContainer.h"

#include "RenderContextRuntime/RenderGraph/RenderGraph.h"
#include "RenderContextRuntime/PSO_PoolDispatcher/PSO_PoolDispatcher.h"

namespace 
{
	auto const fileName = "RenderContext.cpp";
}


RenderContext::RenderContext
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_
) 
{
	Logger::Entry("RenderContext: Constructor");

	pso_PoolDispatcher.reset(new PSO_PoolDispatcher(proof_));
	Logger::Log("Instantiate: PSO_PoolDispatcher", fileName);

	renderPassContainer.reset(new RenderPassContainer(proof_));
	Logger::Log("Instantiate: renderPassContainer", fileName);

	renderPathContainer.reset(new RenderPathContainer(proof_));
	Logger::Log("Instantiate: renderPathContainer", fileName);

	RenderPassCreator passCretor(proof_, renderPassContainer.get());
	Logger::Log("Instantiate: RenderPassCreator", fileName);

	RenderPathAssembler renderPathAssembler
	(
		proof_,
		passCretor, 
		*renderPathContainer
	);
	Logger::Log("Instantiate: renderPathAssembler", fileName);

	renderGraph.reset
	(
		new RenderGraph
		(
			proof_,
			renderPathAssembler,
			*pso_PoolDispatcher,
			*renderPassContainer,
			rootSignatureContextDiplomat_,
			bufferContextDiplomat_,
			modelContextDiplomat_
		)
	);


	Logger::End("RenderContext: Constructor");

}

RenderContext::~RenderContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////