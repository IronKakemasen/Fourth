#include "RenderContext.h"
#include "RenderContextRuntime/PSO_PoolDispatcher/PSO_PoolDispatcher.h"
#include "RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "RenderPass/RenderPassBehavior.h"
#include "RenderPath/RenderPathAssembler/RenderPathAssembler.h"

namespace 
{
	auto const fileName = "RenderContext.cpp";
}


RenderContext::RenderContext(NexusFieldProof proof_, BufferContextDiplomat& bufferContextDiplomat_)
{
	Logger::Entry("RenderContext: Constructor");

	pso_PoolDispatcher.reset(new PSO_PoolDispatcher(proof_));
	Logger::Log("Instantiate: PSO_PoolDispatcher", fileName);

	renderPassContainer.reset(new RenderPassContainer(proof_));
	Logger::Log("Instantiate: renderPassContainer", fileName);

	renderPassCreator.reset(new RenderPassCreator(proof_, renderPassContainer.get(), bufferContextDiplomat_));
	Logger::Log("Instantiate: renderPassCreator", fileName);

	renderPathAssembler.reset(new RenderPathAssembler(proof_, renderPassCreator.get()));
	Logger::Log("Instantiate: renderPathAssembler", fileName);



	Logger::End("RenderContext: Constructor");

}

RenderContext::~RenderContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////