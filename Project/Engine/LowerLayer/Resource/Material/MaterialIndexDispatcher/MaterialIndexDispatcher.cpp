#include "PreCompileHeader.h"
#include "MaterialIndexDispatcher.h"

namespace
{
	auto const fileName = "MaterialIndexDispatcher.cpp";
}


MaterialContext::MaterialIndexDispatcher::MaterialIndexDispatcher(NexusFieldProof proof_)
{
	ReserveMaterialArrDispatchSize<Material::Type::kStandard>();
	ReserveMaterialArrDispatchSize<Material::Type::kGridLine>();

	ErrorMessageOutput::Assert::DetectError
	(
		(UINT)typeSepuence  == Material::kNumParamExists,
		"ReserveMaterialArrDispatchSize()を呼び足りない",
		fileName
	);

	materialIDFreeList.Resize((UINT)ProjectConfig::Render::BufferSize::kMaterialIndexGroupArr,"MaterialIndexGroupArr");

}


UINT MaterialContext::MaterialIndexDispatcher::DispatchMaterialID()
{
	return materialIDFreeList.Distribute();
}
