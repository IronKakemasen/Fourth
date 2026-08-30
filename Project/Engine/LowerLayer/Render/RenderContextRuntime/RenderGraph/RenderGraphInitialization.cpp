#include "RenderGraph.h"
#include "RenderGraphBuilder/GraphicsPSO_Builder/GraphicsPSO_Builder.h"
#include "RenderGraphBuilder/GraphicsRootSigBuilder/GraphicsRootSigBuilder.h"
#include "RenderGraphBuilder/RenderPathBuilder/RenderPathBuilder.h"

void RenderContext::RenderGraph::Build
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	//全てのPathを生成する
	allPathPtr = PathBuilder::InstantiateAllPath(proof_, pathAssembler_, bufferContextDiplomat_);
	
	//ルートシグネチャの生成
	graphicsRootSig = RootSigBuilder::CreateGraphicsRootSig(proof_ , rootSignatureContextDiplomat_);

	//存在しなければならない全てのPSOを生成
	PSO_Builder::CreateAllGraphicsPSO
	(
		proof_ , 
		psoDispatcher_, 
		passContainer,
		modelContextDiplomat_, 
		pso_ContextDiplomat_, 
		shaderContextDiplomat_
	);

}
