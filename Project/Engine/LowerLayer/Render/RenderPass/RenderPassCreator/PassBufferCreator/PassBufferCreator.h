#pragma once
#include "../RenderPassCreator.h"
#include "../../../../Resource/Buffer/BufferContext.h"

struct PassRequiredInfo;

class RenderContext::RenderPassCreator::PassBufferCreator
{
	friend class RenderPassCreator;

	static void CreateBuffer
	(
		std::string const passName_,
		PassRequiredInfo& info, 
		BufferContext::BufferCreator* creator_
	);
};

