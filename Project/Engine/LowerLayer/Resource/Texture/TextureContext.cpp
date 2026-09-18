#include "PreCompileHeader.h"
#include "TextureContext.h"
#include "TextureLibrary/TextureLibrary.h"
#include "TextureBufferCreator/TextureBufferCreator.h"
#include "TextureContextDiplomat/TextureContextDiplomat.h"
#include "TextureContextDiplomat/TextureContextToolLender/TextureContextToolLender.h"



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
	Logger::Entry("TextureContext: Constructor");


	textureLibrary.reset(new TextureLibrary(proof_));
	Logger::Log("Instantiate: TextureLibrary", fileName);

	//ここですべてのコンパイルされたテクスチャファイルを読み込んで、バッファを作る
	TextureBufferCreator textureBufferCreator(proof_, *textureLibrary, bufferContextDiplomat_);

	diplomat.reset
	(
		new TextureContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, textureLibrary.get())
		)
	);
	Logger::Log("Instantiate: TextureContextDiplomat", fileName);
	Logger::Log("Instantiate: ToolLender", fileName);




	Logger::End("TextureContext: Constructor");

}

TextureContext::~TextureContext()
{

}

