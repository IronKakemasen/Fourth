#include "StaticRenderGraph.h"
#include "RenderGraphBuilder/GraphicsPSO_Builder/GraphicsPSO_Builder.h"
#include "RenderGraphBuilder/GraphicsRootSigBuilder/GraphicsRootSigBuilder.h"
#include "RenderGraphBuilder/RenderPathBuilder/RenderPathBuilder.h"
#include "RenderGraphBuilder/PassSetUpper/PassSetUpper.h"

void RenderContext::StaticRenderGraph::Build
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	//全てのPathを生成し、制御シーケンス通りに並び替える
	allPathPtr = PathBuilder::Build(proof_, pathAssembler_, bufferContextDiplomat_);
	
	//グラフィックス用の巨大共通ルートシグネチャ
	graphicsRootSig = RootSigBuilder::Build(proof_, rootSignatureContextDiplomat_);

	//存在しなければならない全てのPSOを生成
	PSO_Builder::Build
	(
		proof_,
		psoDispatcher_,
		passContainer_,
		graphicsRootSig,
		modelContextDiplomat_,
		pso_ContextDiplomat_,
		shaderContextDiplomat_
	);

	//全てのPassの不足している初期化部分(PassInfoの作成、ルートコンスタンツバッファの作成など)を行う。
	refBufSrvIndicesBufferID = PassSetUpper::Setup(proof_, renderPassCreator_, passContainer_, bufferContextDiplomat_);


}
