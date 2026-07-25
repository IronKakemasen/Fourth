#include "PreCompileHeader.h"
#include "BarrierExtractor.h"
#include "../../../../BufferDefinition/GPUBuffer/BufferInterface.h"

template<>
[[nodiscard]] D3D12_RESOURCE_BARRIER BufferContext::BufferUploader::BarrierExtractor::
ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(GPUBufferBehavior* dstBuffer_)
{
	IUpload* uploadBuffer = dynamic_cast<IUpload*>(dstBuffer_);
	ErrorMessageOutput::Assert::DetectError(uploadBuffer, "uploadBufferじゃない", "BufferUploader.h");

	//CommonからCopyDestに遷移させるバリアを吐かせる
	return uploadBuffer->CreateBarrierAsCopy();
}

template<>
[[nodiscard]] D3D12_RESOURCE_BARRIER BufferContext::BufferUploader::BarrierExtractor::
ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(GPUBufferBehavior* dstBuffer_)
{
	IReadOnly* readOnlyBuffer = dynamic_cast<IReadOnly*>(dstBuffer_);
	ErrorMessageOutput::Assert::DetectError(readOnlyBuffer, "リードオンリーなバッファじゃない", "BufferUploader.h");
	
	//コピーからシェーダーリソースに遷移させるバリアを吐かせる
	return readOnlyBuffer->CreateBarrierAsReading();
}




template
[[nodiscard]] D3D12_RESOURCE_BARRIER BufferContext::BufferUploader::BarrierExtractor::
ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(GPUBufferBehavior* dstBuffer_);

template
[[nodiscard]] D3D12_RESOURCE_BARRIER BufferContext::BufferUploader::BarrierExtractor::
ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(GPUBufferBehavior* dstBuffer_);
