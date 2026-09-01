#pragma once
#include "../../RenderGraph.h"
#include "../../../../../Resource/Model/ModelStructure/ModelDescription/ModelDescription.h"
#include "../../../../../Resource/PSO/PSO_Creator/PipelineStateDesc.h"


class RenderContext::RenderGraph::PSO_Builder
{
	friend class RenderGraph;

	//全ての存在せねばならんPSOを生成
	static void CreateAllGraphicsPSO
	(
		NexusFieldProof proof_,
		PSO_PoolDispatcher& psoDispatcher_,
		RenderPassContainer& passContainer_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);


	//以下ヘルパー
private:

	//全モデルデータを受け取ってそのモデルデータのRenderStateのベクタを取り出す
	static std::vector<ModelDescription::RenderState> CollectAllRenderStates(ModelContextDiplomat& modelContextDiplomat_);

	//モデルクラスの情報が必要か否か関係なく埋めれる情報を埋める
	static PipelineStateDesc::Graphics InputCommonInfo(PassDesc const& passDesc_, RenderStateComponent::FillMode const fillMode_);

	//モデルクラスとレンダーパスの二つで残りのPSOの要素を定める
	///引数のpsoDescCommon_には既に共通設定項目が入力されていて、
	///それをベースにRenderStateの数分のPSO_Descを作って追加していく
	static void InputDependingModelsInfo
	(
		ShaderContextDiplomat& shaderContextDiplomat_,
		PipelineStateDesc::Graphics& psoDescCommon_,
		PassDesc const& passDesc_,
		RenderPassComponent::Pass const renderPass_,
		std::vector<ModelDescription::RenderState> const& allRenderStates_,
		std::vector<PipelineStateDesc::Graphics>& allPsoDesc_
	);

	//上と同じ要領
	//レンダーパスオンリーで残りのPSOの要素を定める
	static void InputPassOnlyInfo
	(
		ShaderContextDiplomat& shaderContextDiplomat_, 
		PipelineStateDesc::Graphics const& psoCommonDesc_,
		PassDesc const& passDesc_,
		std::vector<PipelineStateDesc::Graphics>& allPsoDesc_
	);

};

