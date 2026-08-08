#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../../Buffer/BufferContextCmds.h"

class ModelContext::ModelDataCreator::TransformMatrixContainerBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	static void Create
	(
		BufferContext::BufferCreator* bufferCreator_,
		BufferContextCmds::CreateCBufferCmd createCBufferCmd_,
		ModelDataBatcher* modelDataBatcher_
	);

};

