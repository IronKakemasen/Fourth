#pragma once
#include "../ModelSlotAllocator.h"
#include "SimpleFreeList/SimpleFreeList.h"


class ModelContext::ModelSlotAllocator::TransformMatrixSlot
{
public:

	TransformMatrixSlot(NexusFieldProof proof_);

	uint32_t AllocateFreeSlot();

private:

	//TransformMatrixContainerの空きインデックスのリスト
	SimpleFreeList slotList;

};

