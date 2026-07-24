#pragma once
#include "../../BufferUploader.h"

class GPUBufferBehavior;


class BufferContext::BufferUploader::BufferAndResourcePicker
{
	friend class BufferContext::BufferUploader;

	static [[nodiscard]]std::tuple<GPUBufferBehavior*, ID3D12Resource*,std::string> PickBufferAndResource
	(
		BufferContext::BufferDispatcher* dispatcher_,
		BufferUniqueID id_
	);
};

