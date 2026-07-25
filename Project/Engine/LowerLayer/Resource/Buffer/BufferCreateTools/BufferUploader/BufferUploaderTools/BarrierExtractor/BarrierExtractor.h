#pragma once
#include "../../BufferUploader.h"

class BufferContext::BufferUploader::BarrierExtractor
{
	friend class BufferContext::BufferUploader;

	//Copy->ShaderResource
	//Common->Copy
	template<D3D12_RESOURCE_STATES state>
	static [[nodiscard]]D3D12_RESOURCE_BARRIER ExtractBarrier(GPUBufferBehavior* dstBuffer_);

};
