#include "PreCompileHeader.h"
#include "TextureBufferAssembler.h"


//外部
#include "../../../Buffer/BufferDefinition/TextureComponent.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/Texture2DBuffer/Texture2DBuffer.h"
#include "../../../Buffer/BufferDefinition/BufferDescriptions/Texture2DBufferDescription/Texture2DBufferDescription.h"
#include "../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../../Buffer/BufferContextDiplomat/BufferDiplomatIncludes.h"


SRVHeapIndex TextureContext::TextureBufferCreator::BufferAssembler::AssembleTexture2DBuffer
(
	std::string const name_,
	DirectX::ScratchImage& scratchImage_,
	Texture2DState const& texture2DState_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//バッファコンテキストのツールレンダーからいろんなツールを借りる
	auto bufferToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};

	auto* bufferCreator = bufferToolLender->Lend<BufferContext::BufferCreator>(licence);
	auto* bufferUploader = bufferToolLender->Lend<BufferContext::BufferUploader>(licence);

	//ディスクを組み立ててバッファを生成
	Texture2DBufferDescription desc(scratchImage_, texture2DState_);
	auto id_bufferPtr =  bufferCreator->CreateWithBuffer(desc, name_);

	//作成したテクスチャバッファをアップロードリストに追加
	bufferUploader->RegisterTextureBuffer(scratchImage_, id_bufferPtr.first);

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

