#pragma once
#include "../../RenderGraph.h"

class RenderContext::RenderGraph::RootSigBuilder
{
	friend class RenderGraph;

	//グラフィックス用のルートシグの生成
	static [[nodiscard]] ID3D12RootSignature* Build
	(
		NexusFieldProof proof_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_
	);


	//以下ヘルパー
private:

};

