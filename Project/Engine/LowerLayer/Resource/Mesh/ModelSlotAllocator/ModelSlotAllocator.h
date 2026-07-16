#pragma once
#include "../MeshContext.h"
#include "SimpleFreeList/SimpleFreeList.h"

class MeshContext::ModelSlotAllocator
{


public:

	ModelSlotAllocator(MeshContext::InstanceKey key_);
	~ModelSlotAllocator();

private:

	SimpleFreeList 

};

