#include "PreCompileHeader.h"
#include "ModelSlotAllocator.h"
#include "MeshDataIDLibrary/MeshDataIDLibrary.h"
#include "TransformMatrixSlot/TransformMatrixSlot.h"
#include "MaterialSlot/MaterialSlot.h"

namespace
{
	auto const fileName = "ModelSlotAllocator.cpp";
}


ModelContext::ModelSlotAllocator::ModelSlotAllocator(NexusFieldProof proof_)
{

	meshDataIDLibrary.reset(new MeshDataIDLibrary(proof_));
	Logger::Log("Instantiate: MeshDataIDLibrary", fileName);

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
ModelContext::ModelSlotAllocator::MeshDataIDLibrary& ModelContext::ModelSlotAllocator::AccessMeshDataIDLibrary(HandleLicence licence_)
{
	return *meshDataIDLibrary;
}

