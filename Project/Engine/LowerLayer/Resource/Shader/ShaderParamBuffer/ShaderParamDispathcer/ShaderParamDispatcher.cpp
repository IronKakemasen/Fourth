#include "PreCompileHeader.h"
#include "ShaderParamDispatcher.h"


ShaderContext::ShaderParamDispatcher::ShaderParamDispatcher(NexusFieldProof proof_)
{
	ReserveDispatchSize<ShaderParam::Type::kGridLine>();
}


