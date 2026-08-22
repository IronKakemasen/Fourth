#pragma once
#include "../RenderGraph.h"

class RenderContext::RenderGraph::Setupper
{
	friend class RenderGraph;

	static [[nodiscard]] AllPathPtr InstantiateAllPath
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
	static [[nodiscard]] ID3D12RootSignature* CreateGraphicsRootSig(RootSignatureContextDiplomat& rootSignatureContextDiplomat_);
};

