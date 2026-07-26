#pragma once
#include "../../MeshContext.h"

class Model;

class MeshContext::ModelAssembler
{
public:

	ModelAssembler
	(
		NexusFieldProof proof_,
		MeshContext::ModelSlotAllocator* slotAllocator_
	);

	void Assemble(Model& dstModel_);

private:

	MeshContext::ModelSlotAllocator* slotAllocator;

};

