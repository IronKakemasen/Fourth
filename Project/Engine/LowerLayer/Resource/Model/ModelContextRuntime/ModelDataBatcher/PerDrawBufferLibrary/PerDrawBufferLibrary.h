#pragma once
#include "../ModelDataBatcher.h"

class ModelContext::ModelDataBatcher::PerDrawBufferLibrary
{
public:

	PerDrawBufferLibrary(NexusFieldProof proof_);

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void Import(BufferUniqueID uniqueID_)
	{
		bufferIDMap[bufferType] = uniqueID_;
		std::string bufferName = BufferTypeTraits<bufferType>::kBufferName;

		Logger::Log("Import " + bufferName + " UniqueID: " + std::to_string(UINT(uniqueID_)), "PerDrawBufferLibrary.h");
	}

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	BufferUniqueID Export()
	{
		return bufferIDMap[bufferType];
	}


private:

	std::unordered_map<ConstantBuffers::ConstantBufferBindSlots,BufferUniqueID> bufferIDMap;

};

