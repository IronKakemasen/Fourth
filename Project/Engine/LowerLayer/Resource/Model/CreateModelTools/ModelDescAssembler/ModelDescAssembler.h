#pragma once
#include "../../ModelContext.h"
#include "../../ModelStructure/ModelDescription.h"

class ModelContext::ModelDescAssembler
{
	using ModelDescSet = std::pair<std::vector<ModelDescription::Common>, std::vector<ModelDescription::Unique>>;

public:

	ModelDescAssembler
	(
		NexusFieldProof proof_,
		ModelContext::ModelSlotAllocator* slotAllocator_
	);

	//モデルクラスのConfigurable以外のディスクリプションを作ってあげる
	ModelDescSet Assemble(std::string modelFileName_);

private:

	std::vector<ModelDescription::Common> PackCommonData
	(
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	std::vector<ModelDescription::Unique> PackUniqueData(size_t const kNumMeshData_);

	ModelContext::ModelSlotAllocator* slotAllocator;

};


