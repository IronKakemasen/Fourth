#include "PreCompileHeader.h"
#include "TextureBufferAssembler.h"
#include "../../../BufferDefinition/BufferDescriptions/Texture2DBufferDescription/Texture2DBufferDescription.h"
#include "../../BufferCreator.h"
#include "../../BufferUploader/BufferUploader.h"


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



	return SRVHeapIndex{};
}

