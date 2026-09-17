#include "PreCompileHeader.h"
#include "TextureContextDiplomat.h"
#include "TextureContextToolLender/TextureContextToolLender.h"


TextureContextDiplomat::TextureContextDiplomat
(
	TextureContext::NexusFieldProof proof_,
	std::unique_ptr<TextureContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<TextureContext::ToolLender>>(tools) = std::move(toolLender_);
}

