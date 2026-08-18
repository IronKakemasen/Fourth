#include "RenderContext.h"
#include "RenderContextRuntime/PSO_PoolDispatcher/PSO_PoolDispatcher.h"
#include "RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "RenderPass/AllRenderPass/RenderPassBehavior.h"
#include "RenderPath/RenderPathAssembler/RenderPathAssembler.h"
#include "RenderPath/RenderPathContainer/RenderPathContainer.h"
#include "RenderGraph/RenderGraph.h"

namespace 
{
	auto const fileName = "RenderContext.cpp";
}


RenderContext::RenderContext
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_
) 
{
	Logger::Entry("RenderContext: Constructor");

	pso_PoolDispatcher.reset(new PSO_PoolDispatcher(proof_));
	Logger::Log("Instantiate: PSO_PoolDispatcher", fileName);

	renderPassContainer.reset(new RenderPassContainer(proof_));
	Logger::Log("Instantiate: renderPassContainer", fileName);

	renderPathContainer.reset(new RenderPathContainer(proof_));
	Logger::Log("Instantiate: renderPathContainer", fileName);

	std::unique_ptr<RenderPathAssembler> renderPathAssembler = std::make_unique<RenderPathAssembler>
	(
		proof_,
		std::make_unique<RenderPassCreator>(proof_, renderPassContainer.get()),
		renderPathContainer.get(),
		bufferContextDiplomat_
	);
	Logger::Log("Instantiate: RenderPassCreator", fileName);
	Logger::Log("Instantiate: renderPathAssembler", fileName);

	renderGraph.reset
	(
		new RenderGraph
		(
			proof_,
			std::move(renderPathAssembler),
			rootSignatureContextDiplomat_
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