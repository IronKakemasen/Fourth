#include "PreCompileHeader.h"
#include "ShaderContextDiplomat.h"
#include "ShaderContextToolLender/ShaderContextToolLender.h"



ShaderContextDiplomat::ShaderContextDiplomat
(
	ShaderContext::NexusFieldProof proof_,
	std::unique_ptr<ShaderContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<ShaderContext::ToolLender>>(tools) = std::move(toolLender_);
}
