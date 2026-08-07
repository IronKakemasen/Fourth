#pragma once
#include "../ModelDataBatcher.h"

class ModelContext::ModelDataBatcher::ModelUploadBufferUniqueIDs
{
public:
	ModelUploadBufferUniqueIDs(NexusFieldProof proof_);

	template<BufferIDType idType>
	void Import(BufferUniqueID uniqueID_)
	{
		bufferIDs.at(UINT(idType)) = uniqueID_;
		std::string bufferName = BufferTypeTraits<idType>::kBufferName;
		Logger::Log("Import " + bufferName + " UniqueID: " + std::to_string(UINT(uniqueID_)), "ModelUploadBufferUniqueIDs.h");
	}

	template<BufferIDType idType>
	BufferUniqueID Export(BufferUniqueID uniqueID_)
	{
		return bufferIDs[(idType)];
	}


private:

	template<BufferIDType idType>
	struct BufferTypeTraits;


	std::array<BufferUniqueID, (UINT)BufferIDType::kCount> bufferIDs;

};

template<>
struct ModelContext::ModelDataBatcher::ModelUploadBufferUniqueIDs::BufferTypeTraits
<ModelContext::ModelDataBatcher::BufferIDType::kTransformMatrixContainer>
{
	static inline std::string const kBufferName = "TransformMatrixContainer";
};
