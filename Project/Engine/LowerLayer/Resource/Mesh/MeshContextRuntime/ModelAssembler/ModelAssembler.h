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

	void PackCommonData
	(
		Model& dstModel_, 
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	void PackUniqueData
	(
		Model& dstModel_,
		size_t const kNumMeshData_
	);

	MeshContext::ModelSlotAllocator* slotAllocator;

};


