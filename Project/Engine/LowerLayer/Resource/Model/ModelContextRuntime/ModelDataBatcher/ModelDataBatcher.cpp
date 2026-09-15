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
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ModelContext::ModelDataBatcher::BufferType::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ModelContext::ModelDataBatcher::BufferType::kTransformMatrixContainer>(id_);
}

template<>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ModelContext::ModelDataBatcher::BufferType::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ModelContext::ModelDataBatcher::BufferType::kMaterialContainer>(id_);
}


template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ModelContext::ModelDataBatcher::BufferType::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);

template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ModelContext::ModelDataBatcher::BufferType::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);
