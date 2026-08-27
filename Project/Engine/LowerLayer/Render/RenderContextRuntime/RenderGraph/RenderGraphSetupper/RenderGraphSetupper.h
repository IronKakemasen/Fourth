#pragma once
#include "../RenderGraph.h"
#include "../../../../Resource/Model/ModelStructure/ModelDescription/ModelDescription.h"

class Model;

class RenderContext::RenderGraph::Setupper
{
	friend class RenderGraph;

	//全てのPathを生成
	static [[nodiscard]] AllPathPtr InstantiateAllPath
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//グラフィックス用のルートシグの生成
	static [[nodiscard]] ID3D12RootSignature* CreateGraphicsRootSig
	(
		NexusFieldProof proof_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_
	);

	//全ての存在せねばならんPSOを生成
	static void CreateAllGraphicsPSO
	(
		NexusFieldProof proof_,
		PSO_PoolDispatcher& psoDispatcher_,
		RenderPassContainer& passContainer_,
		ModelContextDiplomat& modelContextDiplomat_
	);


	//以下ヘルパー
private:
	
	//全モデルデータを受け取ってそのモデルデータのRenderStateのベクタを取り出す
	static std::vector<ModelDescription::RenderState> 
		CollectAllRenderStates(const std::vector<std::unique_ptr<Model>>* modelData_);

	//全PassからRenderPassComponentの情報を収集する
	static std::unordered_map < RenderPassComponent::Pass, RenderContext::RenderPassState>
		CollectAllRenderPassStates(NexusFieldProof proof_, RenderPassContainer& passContainer_);

};

