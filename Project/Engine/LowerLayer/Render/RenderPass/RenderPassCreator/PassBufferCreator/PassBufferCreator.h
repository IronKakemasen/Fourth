#pragma once
#include "../RenderPassCreator.h"

class RenderContext::RenderPassCreator::PassBufferCreator
{
	friend class RenderPassCreator;

	static void CreateBuffer
	(
		std::string const passName_,
		PassDesc& desc_,
		std::unordered_map<std::string, BufferUniqueID>& passBufferCache_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
};

