#pragma once
#include "../RenderPassCreator.h"
#include "../../../../Resource/Buffer/BufferContext.h"

class RenderContext::RenderPassCreator::PassBufferCreator
{
	friend class RenderPassCreator;

	static void CreateBuffer
	(
		std::string const passName_,
		PassDesc& desc_,
		BufferContext::BufferCreator* creator_
	);
};

