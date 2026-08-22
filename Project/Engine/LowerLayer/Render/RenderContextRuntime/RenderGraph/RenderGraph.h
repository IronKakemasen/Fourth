#pragma once
#include "../../RenderContext.h"
#include "../../RenderPath/AllRenderPath/AllPathFwd.h"


class RenderContext::RenderGraph
{
	class Setupper;

public:

	RenderGraph
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	void Init
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//グラフィックス用の巨大共通ルートシグネチャ
	ID3D12RootSignature* graphicsRootSig;
	//全てのPathのアドレス。本体は別コンテナクラスが所有
	AllPathPtr allPathPtr;


};

