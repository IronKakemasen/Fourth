#pragma once
#include "../../BufferUploader.h"

class BufferContext::BufferUploader::BarrierExtractor
{
	friend class BufferContext::BufferUploader;

	static [[nodiscard]]D3D12_RESOURCE_BARRIER ExtractBarrier(GPUBufferBehavior* dstBuffer_);

		

};
