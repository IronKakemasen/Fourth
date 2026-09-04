#pragma once
#include "../../BufferContext.h"

class BufferContext::TextureBufferCreator
{
	//テクスチャファイルを読み込み、
	class TextureLoader;
	//パルスして、テクスチャバッファのDescを作る
	class TextureBufferDescAssembler;

public:
	TextureBufferCreator
	(
		NexusFieldProof proof_,
		BufferCreator& bufferCreator_,
		BufferCollector& bufferCollector_,
		BufferUploader& bufferUploader_,
		GlobalConstantBufferCreator& globalConstantBufferCreator_,
		TextureLoader& textureLoader_,
		TextureBufferLibrary& textureBufferLibrary_
	);

};

