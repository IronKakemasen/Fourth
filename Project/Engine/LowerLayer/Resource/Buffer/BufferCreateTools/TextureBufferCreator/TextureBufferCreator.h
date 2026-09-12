#pragma once
#include "../../BufferContext.h"

class BufferContext::TextureBufferCreator
{
	//テクスチャファイルのデータが詰まったジェーソンファイルを読み込む
	class TextureDataLoader;
	//テクスチャファイルを読み込む
	class TextureFileLoader;
	//バッファを作りアップロードし(厳密には追加)、そのsrvHeapIndexを返す
	class BufferAssembler;
	//テクスチャバッファのsrvをひとまとまりにしたもののバッファを作成。
	//そのバッファのsrvHeapIndexのグローバル定数バッファを作成
	class GlobalConstantBufferPackager;

public:
	TextureBufferCreator
	(
		NexusFieldProof proof_,
		BufferCreator& bufferCreator_,
		BufferUploader& bufferUploader_,
		GlobalConstantBufferCreator& globalConstantBufferCreator_,
		TextureIndexLibrary& textureBufferLibrary_
	);

};

