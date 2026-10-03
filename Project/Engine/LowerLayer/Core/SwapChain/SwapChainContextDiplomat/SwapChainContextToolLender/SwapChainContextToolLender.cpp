#include "PreCompileHeader.h"
#include "SwapChainContextToolLender.h"


SwapChainContext::ToolLender::ToolLender(NexusFieldProof proof_, SwapChainBuffer* swapChainBuffer_)
{
	std::get<SwapChainBuffer* >(tools) = swapChainBuffer_;
}
