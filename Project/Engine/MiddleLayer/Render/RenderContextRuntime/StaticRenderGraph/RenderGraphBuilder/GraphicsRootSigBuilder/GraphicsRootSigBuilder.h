#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::RootSigBuilder
{
	friend class StaticRenderGraph;

	//グラフィックス用のルートシグの生成
	static [[nodiscard]] BuildOutput::RootSigBuilder Build
	(
		NexusFieldProof proof_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_
	);


	//以下ヘルパー
private:


};

