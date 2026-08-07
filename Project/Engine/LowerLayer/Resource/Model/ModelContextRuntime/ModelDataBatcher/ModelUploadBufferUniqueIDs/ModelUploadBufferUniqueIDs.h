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
		Logger::Log("Import: " + std::to_string(UINT(uniqueID_)));
	}

	template<BufferIDType idType>
	BufferUniqueID Export(BufferUniqueID uniqueID_)
	{
		return bufferIDs[(idType)];
	}


private:

	std::array<BufferUniqueID, (UINT)BufferIDType::kCount> bufferIDs;

};

