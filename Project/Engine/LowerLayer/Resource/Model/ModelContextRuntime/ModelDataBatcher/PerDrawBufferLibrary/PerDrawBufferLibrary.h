#pragma once
#include "../ModelDataBatcher.h"

class ModelContext::ModelDataBatcher::PerDrawBufferLibrary
{
public:
	PerDrawBufferLibrary(NexusFieldProof proof_);

	template<BufferType idType>
	void Import(BufferUniqueID uniqueID_)
	{
		bufferIDs.at(UINT(idType)) = uniqueID_;
		std::string bufferName = BufferTypeTraits<idType>::kBufferName;
		Logger::Log("Import " + bufferName + " UniqueID: " + std::to_string(UINT(uniqueID_)), "PerDrawBufferLibrary.h");
	}

	template<BufferType idType>
	BufferUniqueID Export()
	{
		return bufferIDs[(idType)];
	}


private:

	template<BufferType idType>
	struct BufferTypeTraits;

	std::array<BufferUniqueID, (UINT)BufferType::kCount> bufferIDs;

};

template<>
struct ModelContext::ModelDataBatcher::PerDrawBufferLibrary::BufferTypeTraits
<ModelContext::ModelDataBatcher::BufferType::kTransformMatrixContainer>
{
	static inline std::string const kBufferName = "TransformMatrixContainer";
};

template<>
struct ModelContext::ModelDataBatcher::PerDrawBufferLibrary::BufferTypeTraits
	<ModelContext::ModelDataBatcher::BufferType::kMaterialContainer>
{
	static inline std::string const kBufferName = "MaterialContainer";
};
