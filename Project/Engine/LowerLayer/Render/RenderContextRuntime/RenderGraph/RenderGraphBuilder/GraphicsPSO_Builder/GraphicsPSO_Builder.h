#pragma once
#include "../../RenderGraph.h"
#include "../../../../../Resource/Model/ModelStructure/ModelDescription/ModelDescription.h"
#include "../../../../../Resource/PSO/PSO_Creator/PipelineStateDesc.h"

struct GraphicsPSO_Key;

class RenderContext::RenderGraph::PSO_Builder
{
	friend class RenderGraph;

	using PsoDesc_Key = std::pair<PipelineStateDesc::Graphics, GraphicsPSO_Key>;

	static void Build
	(
		NexusFieldProof proof_,
		PSO_PoolDispatcher& psoDispatcher_,
		RenderPassContainer& passContainer_,
		ID3D12RootSignature* rootSignature_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);


	//以下ヘルパー
private:

	///全ての存在せねばならんPSOのディスクを生成
	static std::vector<PsoDesc_Key> CreateAllPSO_Desc
	(
		NexusFieldProof proof_,
		RenderPassContainer& passContainer_,
		ModelContextDiplomat& modelContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);

	///PSOの生成ディスクから実際にPSOを生成していく
	static void CreateAllPSO
	(
		NexusFieldProof proof_,
		PSO_PoolDispatcher& psoDispatcher_,
		std::vector<PsoDesc_Key>& allDesc_,
		ID3D12RootSignature* rootSignature_,
		PSO_ContextDiplomat& pso_ContextDiplomat_
	);

	//	Logger::Entry("PSO creation start");
	//Logger::Entry("PSO creation end");


	//全モデルデータを受け取ってそのモデルデータのRenderStateのベクタを取り出す
	static std::vector<ModelDescription::RenderState> CollectAllRenderStates(ModelContextDiplomat& modelContextDiplomat_);

	//モデルクラスの情報が必要か否か関係なく埋めれる情報を埋める
	static PsoDesc_Key InputCommonInfo
	(
		RenderPassComponent::Pass const pass_,
		PassDesc const& passDesc_, 
		RenderStateComponent::FillMode const fillMode_
	);

	//モデルクラスとレンダーパスの二つで残りのPSOの要素を定める
	///引数のpsoDescCommon_には既に共通設定項目が入力されていて、
	///それをベースにRenderStateの数分のPSO_Descを作って追加していく
	static void InputDependingModelsInfo
	(
		ShaderContextDiplomat& shaderContextDiplomat_,
		PsoDesc_Key& psoCommonDesc_,
		PassDesc const& passDesc_,
		RenderPassComponent::Pass const renderPass_,
		std::vector<ModelDescription::RenderState> const& allRenderStates_,
		std::vector<PsoDesc_Key>& allPsoDesc_
	);

	//上と同じ要領
	//レンダーパスオンリーで残りのPSOの要素を定める
	static void InputPassOnlyInfo
	(
		ShaderContextDiplomat& shaderContextDiplomat_, 
		PsoDesc_Key& psoCommonDesc_,
		PassDesc const& passDesc_,
		std::vector<PsoDesc_Key>& allPsoDesc_
	);

};

