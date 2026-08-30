#pragma once
#include "../../RenderGraph.h"
#include "../../../../../Resource/Model/ModelStructure/ModelDescription/ModelDescription.h"

class Model;

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



};

