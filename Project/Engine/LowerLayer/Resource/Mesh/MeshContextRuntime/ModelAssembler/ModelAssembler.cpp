#include "PreCompileHeader.h"
#include "ModelAssembler.h"
#include "../../Model/Model.h"
#include "../../Model/ModelDescription.h"
#include "../../CreateModelTools/ModelSlotAllocator/MeshDataIDLibrary/MeshDataIDLibrary.h"

MeshContext::ModelAssembler::ModelAssembler
(
	NexusFieldProof proof_,
	MeshContext::ModelSlotAllocator* slotAllocator_
):slotAllocator(slotAllocator_)
{

}

void MeshContext::ModelAssembler::Assemble(Model& dstModel_)
{
	auto& meshDataIDLib = slotAllocator->AccessMeshDataIDLibrary(MeshContext::ModelSlotAllocator::HandleLicence{});
	const std::vector<MeshDataID>& meshDataIDs = meshDataIDLib.Find(dstModel_.fileName);
	size_t const kNumMeshData = meshDataIDs.size();

	PackCommonData(dstModel_, meshDataIDs, kNumMeshData);
	PackUniqueData(dstModel_, kNumMeshData);

}

void MeshContext::ModelAssembler::PackCommonData
(
	Model& dstModel_,
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

		commons.emplace_back(common);
	}

	dstModel_.modelDataCommons = std::move(commons);

}

void MeshContext::ModelAssembler::PackUniqueData
(
	Model& dstModel_,
	size_t const kNumMeshData_
)
{
	std::vector<ModelDescription::Unique> uniques;
	uniques.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		
		ModelDescription::Unique unique;
		unique.dispatchedTransformedMatrixID =
			slotAllocator->AllocateSlot<MeshContext::ModelSlotAllocator::SlotType::kTransformMatrix>
			(MeshContext::ModelSlotAllocator::AllocateLicence{});

		uniques.emplace_back(unique);
	}

	dstModel_.modelDataUniques = std::move(uniques);
}

