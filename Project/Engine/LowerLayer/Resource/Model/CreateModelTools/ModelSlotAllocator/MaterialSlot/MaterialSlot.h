#pragma once
#include "../ModelSlotAllocator.h"

//外部
#include "SimpleFreeList/SimpleFreeList.h"

class ModelContext::ModelSlotAllocator::MaterialSlot
{
public:

	MaterialSlot(NexusFieldProof proof_);

	uint32_t AllocateFreeSlot();

private:

	//TransformContainerの空きインデックスのリスト
	SimpleFreeList slotList;

};

