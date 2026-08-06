#pragma once
#include "../../ModelDataCreator.h"

class ModelContext::ModelDataCreator::TransformMatrixContainerBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	static void Create
	(
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::ConstantBufferCreator* cBufferCreator_,
		ModelDataBatcher* modelDataBatcher_
	);

};

