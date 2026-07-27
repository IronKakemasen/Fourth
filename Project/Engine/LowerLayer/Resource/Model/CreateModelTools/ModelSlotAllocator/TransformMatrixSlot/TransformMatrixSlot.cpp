#include "PreCompileHeader.h"
#include "TransformMatrixSlot.h"

namespace
{
	auto const fileName = "TransformMatrixSlot.cpp";
}



ModelContext::ModelSlotAllocator::TransformMatrixSlot::TransformMatrixSlot(NexusFieldProof proof_)
{
	//使いまわしTransformMatrixのスロットのサイズを確保する
	transformMatrixSlotList.Resize((UINT)ProjectConfig::Render::GlobalBufferTableSetting::kSizeOfTransformMatrixBufferArray);

}

uint32_t ModelContext::ModelSlotAllocator::TransformMatrixSlot::AllocateFreeSlot()
{
	uint32_t const numAllocated = transformMatrixSlotList.Distribute();
	Logger::Log("Allocate: TransformMatrixSlot[" + std::to_string(numAllocated) + "]", fileName);

	return numAllocated;
}