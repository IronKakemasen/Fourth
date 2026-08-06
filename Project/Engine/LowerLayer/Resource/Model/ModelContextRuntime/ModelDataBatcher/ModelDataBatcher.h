#pragma once
#include "../../ModelContext.h"


class ModelContext::ModelDataBatcher
{
	class ModelUploadBufferUniqueIDs;

public:

	struct Local_InputBufferUniqueIDLicence;

	enum class BufferIDType
	{
		kTransformMatrixContainer


		,kCount
	};

	ModelDataBatcher(NexusFieldProof proof_);
	~ModelDataBatcher();

	template<BufferIDType idType>
	void ImportBufferID(Local_InputBufferUniqueIDLicence licence_,BufferUniqueID id_);


private:

	std::unique_ptr<ModelUploadBufferUniqueIDs> modelUploadBufferUniqueIDs;

};


struct ModelContext::ModelDataBatcher::Local_InputBufferUniqueIDLicence
{
private:

	friend class ModelDataCreator;
	explicit Local_InputBufferUniqueIDLicence() = default;
};


