#include "PreCompileHeader.h"
#include "ModelDataBatcher.h"
#include "PerDrawBufferLibrary/PerDrawBufferLibrary.h"


ModelContext::ModelDataBatcher::ModelDataBatcher(NexusFieldProof proof_)
{
	perDrawBufferLibrary.reset(new PerDrawBufferLibrary(proof_));

}

ModelContext::ModelDataBatcher::~ModelDataBatcher()
{

}

template<>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>(id_);
}

template<>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>(id_);
}


template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);

template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);
