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
	Logger::Log("Check ModelDataLibrary Contents", fileName);

	auto const& meshIDlib= std::get<std::unordered_map<std::string, std::vector<MeshDataID>>>(libTuple);
	auto const& materialLib = std::get<std::unordered_map<std::string, std::vector<MaterialCPU>>>(libTuple);

	for (auto const& [key, value] : meshIDlib)
	{
		std::string mess = key + "::MeshDataID: { ";
		for (size_t i = 0;i < value.size();++i)
		{
			mess += std::to_string((UINT)value[i]);
			mess += (i + 1) < value.size() ? +"," : "";
		}

		mess += " }";
		mess += " Num Materials From File:" + std::to_string(materialLib.at(key).size());

		Logger::Log(mess);
	}
}

