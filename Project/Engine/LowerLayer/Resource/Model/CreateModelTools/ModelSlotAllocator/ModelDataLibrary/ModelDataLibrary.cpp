#include "PreCompileHeader.h"
#include "ModelDataLibrary.h"

namespace
{
	auto const fileName = "ModelDataLibrary.cpp";
}


ModelContext::ModelSlotAllocator::ModelDataLibrary::ModelDataLibrary(NexusFieldProof proof_)
{

}

using namespace StructuredBufferModelData;


void ModelContext::ModelSlotAllocator::ModelDataLibrary::Log()const
{
#ifdef _DEBUG

	Logger::Log("Check ModelDataLibrary Contents", fileName);

	for (auto const& [key, value] : modelData)
	{
		std::string mess = key + "::MeshDataID(sizeMeshlet): { ";

		for (size_t i = 0;i < value.meshDataID.size();++i)
		{
			mess += std::to_string((UINT)value.meshDataID[i]) + "(" + std::to_string(value.meshletSize[i]) + ")";
			mess += (i + 1) < value.meshDataID.size() ? +"," : "";
		}

		mess += " }";
		mess += " Num Materials From File:" + std::to_string(value.materialCPU.size());

		Logger::Log(mess);
	}

#endif // DEBUG

}

