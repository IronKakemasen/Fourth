#include "RenderGraph.h"
#include "RenderGraphBuilder/GraphicsPSO_Builder/GraphicsPSO_Builder.h"
#include "RenderGraphBuilder/GraphicsRootSigBuilder/GraphicsRootSigBuilder.h"
#include "RenderGraphBuilder/RenderPathBuilder/RenderPathBuilder.h"

void RenderContext::RenderGraph::Build
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	//全てのPathを生成し、つなげる
	allPathPtr = PathBuilder::Build(proof_, pathAssembler_, bufferContextDiplomat_);
	
	//グラフィックス用の巨大共通ルートシグネチャ
	ID3D12RootSignature* graphicsRootSig = RootSigBuilder::Build(proof_ , rootSignatureContextDiplomat_);

	//存在しなければならない全てのPSOを生成
	PSO_Builder::Build
	(
		proof_ , 
		psoDispatcher_, 
		passContainer_,
		graphicsRootSig,
		modelContextDiplomat_, 
		pso_ContextDiplomat_, 
		shaderContextDiplomat_
	);

}
