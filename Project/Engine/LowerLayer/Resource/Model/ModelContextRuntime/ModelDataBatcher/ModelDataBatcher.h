#pragma once
#include "../../ModelContext.h"


class ModelContext::ModelDataBatcher
{
	class PerDrawBufferLibrary;

public:

	struct Local_InputBufferUniqueIDLicence;

	enum class BufferType
	{
		kTransformMatrixContainer,
		kMaterialContainer
		

		,kCount
	};

	ModelDataBatcher(NexusFieldProof proof_);
	~ModelDataBatcher();

	template<BufferType idType>
	void ImportPerDrawBufferID(Local_InputBufferUniqueIDLicence licence_,BufferUniqueID id_);


private:

	std::unique_ptr<PerDrawBufferLibrary> perDrawBufferLibrary;

};


struct ModelContext::ModelDataBatcher::Local_InputBufferUniqueIDLicence
{
private:

	friend class ModelDataCreator;
	explicit Local_InputBufferUniqueIDLicence() = default;
};


