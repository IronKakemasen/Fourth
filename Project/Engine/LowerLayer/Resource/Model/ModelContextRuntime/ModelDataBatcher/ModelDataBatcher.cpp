#include "PreCompileHeader.h"
#include "ModelDataBatcher.h"
#include "ModelUploadBufferUniqueIDs/ModelUploadBufferUniqueIDs.h"


ModelContext::ModelDataBatcher::ModelDataBatcher(NexusFieldProof proof_)
{
	modelUploadBufferUniqueIDs.reset(new ModelUploadBufferUniqueIDs(proof_));

}

ModelContext::ModelDataBatcher::~ModelDataBatcher()
{

}

template<>
void ModelContext::ModelDataBatcher::ImportBufferID<ModelContext::ModelDataBatcher::BufferIDType::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	modelUploadBufferUniqueIDs->Import<ModelContext::ModelDataBatcher::BufferIDType::kTransformMatrixContainer>(id_);
}


template
void ModelContext::ModelDataBatcher::ImportBufferID<ModelContext::ModelDataBatcher::BufferIDType::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);
