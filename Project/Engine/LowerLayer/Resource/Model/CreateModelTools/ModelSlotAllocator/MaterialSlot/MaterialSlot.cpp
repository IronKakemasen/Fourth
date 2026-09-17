#include "PreCompileHeader.h"
#include "MaterialSlot.h"

namespace
{
	auto const fileName = "MaterialSlot.cpp";
}


ModelContext::ModelSlotAllocator::MaterialSlot::MaterialSlot(NexusFieldProof proof_)
{
	//使いまわしMaterialSlotのスロットのサイズを確保する
	slotList.Resize((UINT)ProjectConfig::Render::CBufferSize::kSizeOfMaterialContainerBuffer);

}

uint32_t ModelContext::ModelSlotAllocator::MaterialSlot::AllocateFreeSlot()
{
	uint32_t const numAllocated = slotList.Distribute();
	Logger::Log("Allocate: MaterialSlot[" + std::to_string(numAllocated) + "]", fileName);

	return numAllocated;
}