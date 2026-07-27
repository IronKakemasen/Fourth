#pragma once
#include "../../MeshContext.h"
#include "../../Model/ModelDescription.h"

class MeshContext::ModelDescAssembler
{
public:

	ModelDescAssembler
	(
		NexusFieldProof proof_,
		MeshContext::ModelSlotAllocator* slotAllocator_
	);

	void Assemble(std::string modelFileName_);

private:

	std::vector<ModelDescription::Common> PackCommonData
	(
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	std::vector<ModelDescription::Unique> PackUniqueData(size_t const kNumMeshData_);

	MeshContext::ModelSlotAllocator* slotAllocator;

};


