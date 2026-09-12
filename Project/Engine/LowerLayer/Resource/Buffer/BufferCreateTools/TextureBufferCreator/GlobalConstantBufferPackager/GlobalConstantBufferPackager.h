#pragma once
#include "../TextureBufferCreator.h"

class BufferContext::TextureBufferCreator::GlobalConstantBufferPackager
{
	friend class TextureBufferCreator;

	static void Package
	(
		std::vector<SRVHeapIndex> const& indices_,
		BufferCreator& bufferCreator_,
		BufferUploader& bufferUploader_,
		GlobalConstantBufferCreator& globalConstantBufferCreator_
	);
};

