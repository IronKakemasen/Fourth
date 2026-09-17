#include "PreCompileHeader.h"
#include "ModelSlotAllocator.h"
#include "ModelDataLibrary/ModelDataLibrary.h"
#include "TransformMatrixSlot/TransformMatrixSlot.h"
#include "MaterialSlot/MaterialSlot.h"

namespace
{
	auto const fileName = "ModelSlotAllocator.cpp";
}


ModelContext::ModelSlotAllocator::ModelSlotAllocator(NexusFieldProof proof_)
{
	modelDataLibrary.reset(new ModelDataLibrary(proof_));
	Logger::Log("Instantiate: ModelDataLibrary", fileName);

	transformMatrixSlot.reset(new TransformMatrixSlot(proof_));
	Logger::Log("Instantiate: transformMatrixSlot", fileName);

	materialSlot.reset(new MaterialSlot(proof_));
	Logger::Log("Instantiate: MaterialSlot", fileName);

}

ModelContext::ModelSlotAllocator::~ModelSlotAllocator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
uint32_t ModelContext::ModelSlotAllocator::AllocateSlot
<ModelContext::ModelSlotAllocator::TransformMatrixSlot>(AllocateLicence licence_)
{
	return transformMatrixSlot->AllocateFreeSlot();
}

template<>
uint32_t ModelContext::ModelSlotAllocator::AllocateSlot
<ModelContext::ModelSlotAllocator::MaterialSlot>(AllocateLicence licence_)
{
	return materialSlot->AllocateFreeSlot();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelContext::ModelSlotAllocator::ModelDataLibrary& ModelContext::ModelSlotAllocator::AccessModelDataLibrary(HandleLicence licence_)
{
	return *modelDataLibrary;
}

