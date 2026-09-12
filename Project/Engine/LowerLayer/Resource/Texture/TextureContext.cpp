#include "PreCompileHeader.h"
#include "TextureContext.h"
#include "TextureLibrary/TextureLibrary.h"
#include "TextureBufferCreator/TextureBufferCreator.h"

namespace
{
	auto fileName = "TextureContext.cpp";
}


TextureContext::TextureContext
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	Logger::Entry("ShaderContext: Constructor");


	textureLibrary.reset(new TextureLibrary(proof_));
	Logger::Log("Instantiate: TextureLibrary", fileName);

	TextureBufferCreator textureBufferCreator(proof_, *textureLibrary, bufferContextDiplomat_);





	Logger::End("ShaderContext: Constructor");

}

TextureContext::~TextureContext()
{

}

