#include "PreCompileHeader.h"
#include "MaterialIndexDispatcher.h"


MaterialContext::MaterialIndexDispatcher::MaterialIndexDispatcher(NexusFieldProof proof_)
{
	ReserveDispatchSize<Material::Type::kStandard>();
	ReserveDispatchSize<Material::Type::kGridLine>();


	ErrorMessageOutput::Assert::DetectError
	(
		(UINT)typeSepuence  == Material::kNumParamExists,
		"ReserveDispatchSize()を呼び足りない",
		"MaterialIndexDispatcher.cpp"
	);


}


