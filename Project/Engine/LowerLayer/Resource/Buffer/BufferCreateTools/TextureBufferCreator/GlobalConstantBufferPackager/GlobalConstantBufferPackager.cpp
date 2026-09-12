//#include "PreCompileHeader.h"
//#include "GlobalConstantBufferPackager.h"
//#include "../../BufferUploader/BufferUploader.h"
//#include "../../BufferCreator.h"
//#include "../../../GlobalConstantBuffers/GlobalConstantBufferCreator/GlobalConstantBufferCreator.h"
//#include "../../../BufferDefinition/BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"
//#include "../../../BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"
//
//void BufferContext::TextureBufferCreator::GlobalConstantBufferPackager::Package
//(
//	std::vector<SRVHeapIndex> const& indices_,
//	BufferCreator& bufferCreator_,
//	BufferUploader& bufferUploader_,
//	GlobalConstantBufferCreator& globalConstantBufferCreator_
//)
//{
//	//まずはindicesのstaticStructuredBufferを作ってアップロードする
//	//ディスク作って
//	StaticStructuredBufferDescription desc((UINT)sizeof(SRVHeapIndex), (UINT)indices_.size(), 0);
//	//バッファ生成して
//	auto id_buffer = bufferCreator_.CreateWithBuffer(desc, "TextureIndices");
//	//アップロードリストに登録
//	bufferUploader_.RegisterBuffer(id_buffer.first, (UINT)indices_.size(), indices_.data());
//
//	//globalConstantBufferCreator_.ProvideCreateCBufferCmd(ProviderKey{});
//
//
//}
