#pragma once
#include "../../RenderContext.h"
#include "../../RenderPath/AllRenderPath/AllPathFwd.h"


class RenderContext::RenderGraph
{
	class Builder;

public:

	RenderGraph
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
	);

private:

	void Build
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
	);

	//グラフィックス用の巨大共通ルートシグネチャ
	ID3D12RootSignature* graphicsRootSig;
	//全てのPathのアドレス。本体は別コンテナクラスが所有
	AllPathPtr allPathPtr;


};

