#pragma once
#include "../TextureBufferCreator.h"

class TextureContext::TextureBufferCreator::GlobalConstantBufferPackager
{
	friend class TextureBufferCreator;

	static void Package
	(
		std::vector<SRVHeapIndex> const& indices_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
};

