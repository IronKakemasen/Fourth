#pragma once
#include "../../RenderGraph.h"

class RenderContext::RenderGraph::PathBuilder
{
	friend class RenderGraph;



	//以下ヘルパー
private:

	//全てのPathを生成
	static AllPathPtr InstantiateAllPath
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

};

