#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::PathBuilder
{
	friend class StaticRenderGraph;



	//以下ヘルパー
private:

	//全てのPathを生成
	static AllPathPtr Build
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

};

