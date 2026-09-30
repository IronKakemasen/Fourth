#pragma once
#include "../../StaticRenderGraph.h"
#include "../../../../RenderStateComponent.h"

class RenderContext::StaticRenderGraph::PathOperator
{
public:

	PathOperator
	(
		NexusFieldProof proof_,
		std::vector<PathBehavior*> const& allPathPtr_,
		PSO_PoolDispatcher& pso_PoolDispatcher_
	);

	//全pathの更新処理をぶん回す
	void Run
	(
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		RuntimeWrapper& runtimeWrapper_
	);

private:

	PSO_PoolDispatcher& pso_PoolDispatcher;
	//モデル描画用のフィルモード
	RenderStateComponent::FillMode modelFillMode = RenderStateComponent::FillMode::kSolid;
	//シーケンス順にソートされた、全てのPathのポインタ
	std::vector<PathBehavior*> allPathPtr;

};

