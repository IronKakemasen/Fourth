#include "PreCompileHeader.h"
#include "PSO_ContextToolLender.h"
#include "../../PSO_Creator/PSO_Creator.h"

PSO_Context::ToolLender::ToolLender(NexusFieldProof proof_, PSO_Creator* creator_)
{
	std::get<PSO_Creator*>(tools) = creator_;
}