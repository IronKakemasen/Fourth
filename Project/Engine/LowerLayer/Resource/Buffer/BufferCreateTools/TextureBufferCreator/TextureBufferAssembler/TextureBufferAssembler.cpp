#include "PreCompileHeader.h"
#include "TextureBufferAssembler.h"
#include "../../../BufferDefinition/BufferDescriptions/Texture2DBufferDescription/Texture2DBufferDescription.h"
#include "../../BufferCreator.h"
#include "../../BufferUploader/BufferUploader.h"
#include "../../../BufferDefinition/AllBuffersInclude.h"


SRVHeapIndex BufferContext::TextureBufferCreator::BufferAssembler::AssembleTexture2DBuffer
(
	std::string const name_,
	DirectX::ScratchImage& scratchImage_,
	Texture2DState texture2DState_,
	BufferCreator& bufferCreator_,
	BufferUploader& bufferUploader_
)
{
	//ディスクを組み立ててバッファを生成
	Texture2DBufferDescription desc(scratchImage_, texture2DState_);
	auto id_bufferPtr =  bufferCreator_.CreateWithBuffer(desc, name_);

	//作成したテクスチャバッファをアップロードリストに追加
	bufferUploader_.RegisterTextureBuffer(scratchImage_, id_bufferPtr.first);

	//最後にこのバッファのsrvHeapIndexをかえす
	Texture2DBuffer* tex2DBuffer = static_cast<Texture2DBuffer*>(id_bufferPtr.second);
	IReadable* readableBuffer = dynamic_cast<IReadable*>(tex2DBuffer);
	ErrorMessageOutput::Assert::DetectError
	(
		readableBuffer,
		id_bufferPtr.second->WatchName() + "がIReadableじゃない",
		"TextureBufferAssembler.cpp"
	);

	return readableBuffer->OutProperSRVHeapIndex(0);
}

