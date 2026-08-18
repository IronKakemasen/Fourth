#pragma once
#include "../RenderContext.h"

class RenderContext::RenderGraph
{
public:

	RenderGraph
	(
		NexusFieldProof proof_,
		std::unique_ptr<RenderPathAssembler>&& pathAssembler_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_
	);

private:

};

