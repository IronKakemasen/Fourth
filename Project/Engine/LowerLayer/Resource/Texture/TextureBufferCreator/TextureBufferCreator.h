#pragma once
#include "../TextureContext.h"

class TextureContext::TextureBufferCreator
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
		TextureLibrary& textureLibrary_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

};

