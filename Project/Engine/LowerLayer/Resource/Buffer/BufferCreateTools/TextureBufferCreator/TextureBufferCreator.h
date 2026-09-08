#pragma once
#include "../../BufferContext.h"

class BufferContext::TextureBufferCreator
{
	//テクスチャファイルを読み込み、
	class TextureDataLoader;
	//パルスして、テクスチャバッファのDescを作る
	class TextureBufferDescAssembler;

public:
	TextureBufferCreator
	(
		NexusFieldProof proof_,
		BufferCreator& bufferCreator_,
		BufferUploader& bufferUploader_,
		GlobalConstantBufferCreator& globalConstantBufferCreator_,
		TextureBufferLibrary& textureBufferLibrary_
	);

};

