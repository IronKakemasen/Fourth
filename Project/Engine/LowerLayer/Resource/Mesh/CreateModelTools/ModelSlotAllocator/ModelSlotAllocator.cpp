#include "PreCompileHeader.h"
#include "ModelSlotAllocator.h"

namespace
{
	auto const fileName = "ModelSlotAllocator.cpp";
}


MeshContext::ModelSlotAllocator::ModelSlotAllocator(MeshContext::InstanceKey key_)
{
	//使いまわしTransformMatrixのスロットのサイズを確保する
	for (UINT i = 0;i < (UINT)ProjectConfig::Render::GlobalBufferTableSetting::kSizeOfTransformMatrixBufferArray;++i)
	{
		transformMatrixSlotList.Add(i);
	}

}

MeshContext::ModelSlotAllocator::~ModelSlotAllocator()
{

}

void MeshContext::ModelSlotAllocator::LinkModelFileNameToMeshDataID
(
	CreateModelDataLicence licence_,
	std::string modelFileName_,
	const std::vector<MeshDataID>& idContainer_
) 
{
	//いちおう
	ErrorMessageOutput::Assert::DetectError(idContainer_.size() > 0, "中身すっからかんやん！", fileName);

	meshDataIDLib[modelFileName_] = idContainer_;
	Logger::Log("Register: " + modelFileName_ + " MeshDataIDs", fileName);
}

void MeshContext::ModelSlotAllocator::SetMeshDataSRVHeapIndexGroupArraySRVHeapIndex(std::unique_ptr<SRVHeapIndex>&& index_)
{
	meshDataSRVHeapIndexGroupArraySRVHeapIndex = std::move(index_);
}


template<> uint32_t MeshContext::ModelSlotAllocator::
DistributeSlot<MeshContext::ModelSlotAllocator::SlotType::kTransformMatrix>(DistributeLicence licence_)
{
	return transformMatrixSlotList.Distribute();
}







template uint32_t MeshContext::ModelSlotAllocator::
DistributeSlot<MeshContext::ModelSlotAllocator::SlotType::kTransformMatrix>(DistributeLicence licence_);
