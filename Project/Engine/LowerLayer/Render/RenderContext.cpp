
#include "RenderContext.h"
#include "PSO_PoolDispatcher/PSO_PoolDispatcher.h"

namespace 
{
	auto const fileName = "RenderContext.cpp";
}


RenderContext::RenderContext(InstacnceKey key_)
{
	Logger::Entry("RenderContext: Constructor");

	pso_PoolDispatcher.reset(new PSO_PoolDispatcher(key_, &graphicsPSO_pool));
	Logger::Log("Instantiate: PSO_PoolDispatcher", fileName);



	Logger::End("RenderContext: Constructor");

}

RenderContext::~RenderContext()
{

}