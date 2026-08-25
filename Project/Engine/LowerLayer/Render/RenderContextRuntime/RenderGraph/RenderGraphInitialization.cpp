#include "RenderGraph.h"
#include "RenderGraphSetupper/RenderGraphSetupper.h"

void RenderContext::RenderGraph::Init
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_

)
{
	//全てのPathを生成する
	Setupper::InstantiateAllPath(proof_, pathAssembler_, bufferContextDiplomat_);
	
	//ルートシグネチャの生成
	graphicsRootSig = Setupper::CreateGraphicsRootSig(rootSignatureContextDiplomat_);

	//存在しなければならない全てのPSOを生成
	Setupper::CreateAllGraphicsPSO(psoDispatcher_, modelContextDiplomat_);

}
