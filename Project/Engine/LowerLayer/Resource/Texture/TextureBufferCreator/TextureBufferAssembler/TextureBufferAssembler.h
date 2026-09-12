#pragma once
#include "../TextureBufferCreator.h"

//外部
#include "../../../../../../External/DirectXTex/DirectXTex.h"


struct Texture2DState;

class TextureContext::TextureBufferCreator::BufferAssembler
{
	friend class TextureBufferCreator;

	static SRVHeapIndex AssembleTexture2DBuffer
	(
		std::string const name_,
		DirectX::ScratchImage& scratchImage_,
		Texture2DState const& texture2DState_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

};

