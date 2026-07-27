#include "PreCompileHeader.h"
#include "ModelDescAssembler.h"
#include "../../CreateModelTools/ModelSlotAllocator/MeshDataIDLibrary/MeshDataIDLibrary.h"

ModelContext::ModelDescAssembler::ModelDescAssembler
(
	NexusFieldProof proof_,
	ModelContext::ModelSlotAllocator* slotAllocator_
):slotAllocator(slotAllocator_)
{

}

ModelContext::ModelDescAssembler::ModelDescSet ModelContext::ModelDescAssembler::Assemble(std::string modelFileName_)
{
	auto& meshDataIDLib = slotAllocator->AccessMeshDataIDLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
	const std::vector<MeshDataID>& meshDataIDs = meshDataIDLib.Find(modelFileName_);
	size_t const kNumMeshData = meshDataIDs.size();

	return std::make_pair(PackCommonData(meshDataIDs, kNumMeshData), PackUniqueData(kNumMeshData));
}

std::vector<ModelDescription::Common> ModelContext::ModelDescAssembler::PackCommonData
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

std::vector<ModelDescription::Unique> ModelContext::ModelDescAssembler::PackUniqueData(size_t const kNumMeshData_)
{
	std::vector<ModelDescription::Unique> uniques;
	uniques.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		
		ModelDescription::Unique unique;
		unique.dispatchedTransformedMatrixID =
			slotAllocator->AllocateSlot<ModelContext::ModelSlotAllocator::TransformMatrixSlot>
			(ModelContext::ModelSlotAllocator::AllocateLicence{});

		uniques[i] = std::move(unique);

	}

	return uniques;
}

