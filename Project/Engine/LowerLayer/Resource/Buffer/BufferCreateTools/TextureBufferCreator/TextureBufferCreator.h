#pragma once
#include "../../BufferContext.h"

class BufferContext::TextureBufferCreator
{
	//テクスチャファイルのデータが詰まったジェーソンファイルを読み込む
	class TextureDataLoader;
	//テクスチャファイルを読み込む
	class TextureFileLoader;

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

