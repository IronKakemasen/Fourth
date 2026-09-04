#include "PreCompileHeader.h"
#include "TextureBufferCreator.h"
#include "../BufferCreator.h"
#include "../BufferCollector/BufferCollector.h"
#include "../BufferUploader/BufferUploader.h"
#include "TextureLoader/TextureLoader.h"
#include "TextureBufferDescAssembler/TextureBufferDescAssembler.h"



BufferContext::TextureBufferCreator::TextureBufferCreator
(
	NexusFieldProof proof_,
	BufferCreator& bufferCreator_,
	BufferCollector& bufferCollector_,
	BufferUploader& bufferUploader_,
	GlobalConstantBufferCreator& globalConstantBufferCreator_,
	TextureLoader& textureLoader_,
	TextureBufferLibrary& textureBufferLibrary_
)
{
	///目標
	//全てのテクスチャファイルを読み込み、バッファを作成してlibraryにつめていく。
	//全バッファのsrvをひとまとまりにしたものをStaticStructuredBufferとして作成し、アップロード
	//そのバッファのsrvIndexをさらにGlobalConstantBufferで送る






}
