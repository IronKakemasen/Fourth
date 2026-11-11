#include "PreCompileHeader.h"
#include "MaterialIndexDispatcher.h"


MaterialContext::MaterialIndexDispatcher::MaterialIndexDispatcher(NexusFieldProof proof_)
{
	ReserveMaterialArrDispatchSize<Material::Type::kStandard>();
	ReserveMaterialArrDispatchSize<Material::Type::kGridLine>();

	ErrorMessageOutput::Assert::DetectError
	(
		(UINT)typeSepuence  == Material::kNumParamExists,
		"ReserveMaterialArrDispatchSize()を呼び足りない",
		"MaterialIndexDispatcher.cpp"
	);

	materialIDFreeList.Resize((UINT)ProjectConfig::Render::BufferSize::kMaterialIndexGroupArr,"MaterialIndexGroupArr");

}


UINT MaterialContext::MaterialIndexDispatcher::DispatchMaterialID()
{
	return materialIDFreeList.Distribute();
}


void MaterialContext::MaterialIndexDispatcher::ImportMaterialIDGroupArrBufferID(BufferUniqueID id_)
{
	materialIDGroupArrBufferID = id_;
	Logger::Log("Import MaterialIDGroupArrBufferID: " + std::to_string(id_), "MaterialIndexDispatcher.cpp");
}



