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
		PSO_PoolDispatcher& pso_PoolDispatcher_,
		std::vector<BufferTraits::BufferTag> const& traceRefBuffersTag_,
		std::array<std::vector<BufferUniqueID>, BuildOutput::PassSetUpper::kNumRefBufferType> const& refBuffersArr_,
		BufferUniqueID const targetFillInRefBufferID_
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

	//全Pass分の参照テクスチャを更新する
	void FillInRefBufferSrvIndices
	(
		UINT const frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	PSO_PoolDispatcher& pso_PoolDispatcher;
	//モデル描画用のフィルモード
	RenderStateComponent::FillMode modelFillMode = RenderStateComponent::FillMode::kSolid;
	//シーケンス順にソートされた、全てのPathのポインタ
	std::vector<PathBehavior*> allPathPtr;


	///全てのパスが参照するバッファのID群のうちどちらなのかを識別するためのもの
	std::vector<BufferTraits::BufferTag> traceRefBuffersTag;
	//参照バッファのID情報源
	std::array<std::vector<BufferUniqueID>, BuildOutput::PassSetUpper::kNumRefBufferType> const& refBuffersArr;
	//参照バッファのsrvheapIndex群を入れておくため
	std::vector<SRVHeapIndex> refBufferSrvIndices;

	///パスが参照するバッファのsrvHeapIndexを詰めるためのバッファのID
	BufferUniqueID targetFillInRefBufferID;


};

