#include "RenderGraph.h"
#include "RenderGraphSetupper/RenderGraphSetupper.h"

void RenderContext::RenderGraph::Init
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_

)
{
	//全てのPathを生成する
	allPathPtr = Setupper::InstantiateAllPath(proof_, pathAssembler_, bufferContextDiplomat_);
	
	//ルートシグネチャの生成
	graphicsRootSig = Setupper::CreateGraphicsRootSig(proof_ , rootSignatureContextDiplomat_);

	//存在しなければならない全てのPSOを生成
	Setupper::CreateAllGraphicsPSO(proof_ , psoDispatcher_, passContainer,modelContextDiplomat_);

}
