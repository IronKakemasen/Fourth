#include "PreCompileHeader.h"
#include "RootSignatureToolLender.h"


RootSignatureContext::ToolLender::ToolLender(NexusFieldProof proof_, RootSignatureCreator* creator_)
{
	std::get<RootSignatureCreator*>(tools) = creator_;
}
