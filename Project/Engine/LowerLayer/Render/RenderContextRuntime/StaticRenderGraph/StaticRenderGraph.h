#pragma once
#include "../../RenderContext.h"
#include "../../RenderPath/AllRenderPath/AllPathFwd.h"
#include "../../RenderPass/RenderPassComponent.h"

class RenderContext::StaticRenderGraph
{
	class PSO_Builder;
	class PathBuilder;
	class RootSigBuilder;
	class PassSetUpper;
	
	//Pathのランタイムを制御する
	class PathOperator;
	//共通描画コマンドをたたく
	class CommonCmdExecutor;

public:

	StaticRenderGraph
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		PSO_PoolDispatcher& psoDispatcher_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);

	~StaticRenderGraph();
private:

	void Build
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
	);

	//全てのPathのアドレス。本体は別コンテナクラスが所有。制御シーケンス通りにソートされている
	std::vector<PathBehavior*> allPathPtr;
	//パスが参照するバッファのsrvheapIndexがつまったバッファID
	//ランタイムで更新する必要がある
	BufferUniqueID refBufSrvIndicesBufferID;
	//描画用巨大共通ルートシグネチャ
	ID3D12RootSignature* graphicsRootSig;

	std::unique_ptr<PathOperator> pathOperator;
	std::unique_ptr<CommonCmdExecutor> commonCmdExecutor;

	
};

