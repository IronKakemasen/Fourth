#include "PreCompileHeader.h"
#include "ModelSlotAllocator.h"



MeshContext::ModelSlotAllocator::ModelSlotAllocator(MeshContext::InstanceKey key_)
{
	for (UINT i = 0;i < (UINT)ProjectConfig::Render::GlobalBufferTableSetting::kSizeOfTransformMatrixBufferArray;++i)
	{
		transformMatrixSlotList.Add(i);
	}

}

MeshContext::ModelSlotAllocator::~ModelSlotAllocator()
{

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
