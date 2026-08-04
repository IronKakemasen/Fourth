#include "PreCompileHeader.h"
#include "ShaderContextToolLender.h"


ShaderContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	ShaderContext::ShaderLibrary* shaderLibrary_
)
{
	std::get<ShaderContext::ShaderLibrary*>(tools) = shaderLibrary_;
}
