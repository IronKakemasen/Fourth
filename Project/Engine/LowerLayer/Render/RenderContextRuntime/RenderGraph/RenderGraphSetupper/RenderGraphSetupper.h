#pragma once
#include "../RenderGraph.h"

struct ModelDescription;
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
	static [[nodiscard]] ID3D12RootSignature* CreateGraphicsRootSig(RootSignatureContextDiplomat& rootSignatureContextDiplomat_);

	//全ての存在せねばならんPSOを生成
	static void CreateAllGraphicsPSO(PSO_PoolDispatcher& psoDispatcher_,ModelContextDiplomat& modelContextDiplomat_);


	//以下ヘルパー
private:
	
	//全モデルデータを受け取ってそのモデルデータのRenderStateのベクタを取り出す
	static void ExtractModelDescription
	(
		std::vector<ModelDescription const*>& dst_,
		const std::vector<std::unique_ptr<Model>>* modelData_
	);

};

