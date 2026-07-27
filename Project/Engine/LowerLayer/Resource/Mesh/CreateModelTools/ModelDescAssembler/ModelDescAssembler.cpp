#include "PreCompileHeader.h"
#include "ModelDescAssembler.h"
#include "../../CreateModelTools/ModelSlotAllocator/MeshDataIDLibrary/MeshDataIDLibrary.h"

MeshContext::ModelDescAssembler::ModelDescAssembler
(
	NexusFieldProof proof_,
	MeshContext::ModelSlotAllocator* slotAllocator_
):slotAllocator(slotAllocator_)
{

}

void MeshContext::ModelDescAssembler::Assemble(std::string modelFileName_)
{
	auto& meshDataIDLib = slotAllocator->AccessMeshDataIDLibrary(MeshContext::ModelSlotAllocator::HandleLicence{});
	const std::vector<MeshDataID>& meshDataIDs = meshDataIDLib.Find(modelFileName_);
	size_t const kNumMeshData = meshDataIDs.size();

	PackCommonData(meshDataIDs, kNumMeshData);
	PackUniqueData(kNumMeshData);

}

std::vector<ModelDescription::Common> MeshContext::ModelDescAssembler::PackCommonData
(
	const std::vector<MeshDataID>& meshDataIDs_,
	size_t const kNumMeshData_
)
{

	std::vector<ModelDescription::Common> commons;
	commons.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		ModelDescription::Common common;
		common.meshDataID = meshDataIDs_[i];

		commons[i] = std::move(common);
	}

	return commons;
}

std::vector<ModelDescription::Unique> MeshContext::ModelDescAssembler::PackUniqueData(size_t const kNumMeshData_)
{
	std::vector<ModelDescription::Unique> uniques;
	uniques.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		
		ModelDescription::Unique unique;
		unique.dispatchedTransformedMatrixID =
			slotAllocator->AllocateSlot<MeshContext::ModelSlotAllocator::SlotType::kTransformMatrix>
			(MeshContext::ModelSlotAllocator::AllocateLicence{});

		uniques[i] = std::move(unique);

	}

	return uniques;
}

