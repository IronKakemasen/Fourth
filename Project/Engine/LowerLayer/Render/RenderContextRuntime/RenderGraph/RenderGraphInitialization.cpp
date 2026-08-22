#include "RenderGraph.h"
#include "RenderGraphSetupper/RenderGraphSetupper.h"

void RenderContext::RenderGraph::Init
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//全てのPathを生成する
	Setupper::InstantiateAllPath(proof_, pathAssembler_, bufferContextDiplomat_);
	

	//ルートシグネチャの生成
	graphicsRootSig = Setupper::CreateGraphicsRootSig(rootSignatureContextDiplomat_);

}
