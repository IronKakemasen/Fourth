#include "PreCompileHeader.h"
#include "MaterialIndexDispatcher.h"


MaterialContext::MaterialIndexDispatcher::MaterialIndexDispatcher(NexusFieldProof proof_)
{
	ReserveDispatchSize<Material::Type::kGridLine>();
}


