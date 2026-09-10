#pragma once
#include "../TextureBufferCreator.h"
#include "../../../BufferDefinition/TextureComponent.h"

//外部
#include "../../../../../../../External/DirectXTex/DirectXTex.h"

class BufferContext::TextureBufferCreator::BufferAssembler
{
	friend class TextureBufferCreator;

	static SRVHeapIndex AssembleTexture2DBuffer
	(
		std::string const name_,
		DirectX::ScratchImage& scratchImage_,
		Texture2DState texture2DState_,
		BufferCreator& bufferCreator_,
		BufferUploader& bufferUploader_
	);

};

