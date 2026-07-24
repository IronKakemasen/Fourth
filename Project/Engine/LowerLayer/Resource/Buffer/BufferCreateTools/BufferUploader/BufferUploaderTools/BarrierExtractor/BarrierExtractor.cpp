#include "PreCompileHeader.h"
#include "BarrierExtractor.h"
#include "../../../../BufferDefinition/GPUBuffer/BufferInterface.h"

[[nodiscard]] D3D12_RESOURCE_BARRIER BufferContext::BufferUploader::BarrierExtractor::ExtractBarrier(GPUBufferBehavior* dstBuffer_)
{
	IReadOnly* readOnlyBuffer = dynamic_cast<IReadOnly*>(dstBuffer_);
	ErrorMessageOutput::Assert::DetectError(readOnlyBuffer, "リードオンリーなバッファじゃない", "BufferUploader.h");
	//コピーからシェーダーリソースに遷移させるバリアを吐かせる
	return readOnlyBuffer->CreateBarrierAsReading();
}
