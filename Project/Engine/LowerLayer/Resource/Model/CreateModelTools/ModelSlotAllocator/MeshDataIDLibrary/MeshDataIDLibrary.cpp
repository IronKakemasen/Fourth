#include "PreCompileHeader.h"
#include "MeshDataIDLibrary.h"

namespace
{
	auto const fileName = "MeshDataIDLibrary.cpp";
}


ModelContext::ModelSlotAllocator::MeshDataIDLibrary::MeshDataIDLibrary(NexusFieldProof proof_)
{

}


void ModelContext::ModelSlotAllocator::MeshDataIDLibrary::LinkModelFileNameToMeshDataID
(
	std::string modelFileName_,
	const std::vector<MeshDataID>& idContainer_
)
{
	//いちおう
	ErrorMessageOutput::Assert::DetectError(idContainer_.size() > 0, "中身すっからかんやん！", fileName);

	meshDataIDLib[modelFileName_] = idContainer_;
	Logger::Log("Register: " + modelFileName_ + " MeshDataIDs", fileName);
}

void ModelContext::ModelSlotAllocator::MeshDataIDLibrary::Log()const
{
	Logger::Log("Check MeshDataIdLibrary Contents", fileName);

	for (auto [key, value] : meshDataIDLib)
	{
		std::string mess = key + "::MeshDataID: { ";
		for (size_t i = 0;i < value.size();++i)
		{
			mess += std::to_string((UINT)value[i]);
			mess += (i + 1) < value.size() ? +"," : "";
		}

		Logger::Log(mess + " }");

	}
}

[[nodiscard]] const std::vector<MeshDataID>& ModelContext::ModelSlotAllocator::MeshDataIDLibrary::Find(std::string fileName_)const
{
	ErrorMessageOutput::Assert::DetectError
	(
		meshDataIDLib.find(fileName_) != meshDataIDLib.end(),
		"そないなキーはありません",
		fileName
	);

	return meshDataIDLib.at(fileName_);
}
