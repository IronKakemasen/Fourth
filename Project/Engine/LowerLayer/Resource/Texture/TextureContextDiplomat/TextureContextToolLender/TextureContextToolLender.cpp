#include "PreCompileHeader.h"
#include "TextureContextToolLender.h"
#include "../../TextureLibrary/TextureLibrary.h"



TextureContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	TextureLibrary* textureLibrary_
)
{
	std::get<TextureLibrary*>(tools) = textureLibrary_;
}
