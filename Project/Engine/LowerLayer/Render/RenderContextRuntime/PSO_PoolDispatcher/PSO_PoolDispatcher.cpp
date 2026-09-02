#include "PSO_PoolDispatcher.h"


namespace
{
	auto const fileName = "PSO_PoolDispatcher.cpp";
}


RenderContext::PSO_PoolDispatcher::PSO_PoolDispatcher
(
	NexusFieldProof proof_
)
{
	DefinePackageLayout();
	closedHashMap.reset(new ClosedHashMap<uint32_t>(kHashMapCapacity));
	
}

RenderContext::PSO_PoolDispatcher::~PSO_PoolDispatcher()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PSO_PoolDispatcher::DefinePackageLayout()
{
	keyPackager.reset
	(
		new KeyPackager
		(
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kPass>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kMeshType>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kMaterialType>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kBlendMode>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::KFillMode>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kCullMode>()
		)
	);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::optional<uint32_t> RenderContext::PSO_PoolDispatcher::CheckDuplication(const GraphicsPSO_Key& psoKey_)
{
	uint32_t const packedKey = PackKey(psoKey_);

	//今回はpsoPoolIndexは利用しない
	///dstMapIndexに実体があれば新しくPSOをHashMapのここに生成してねという値
	std::pair<std::optional<uint32_t>, std::optional<uint32_t>> psoPoolIndex_dstMapIndex =
		closedHashMap->CheckDuplication(packedKey);

	///dstMapIndexチェックしてPSOを生成するか分岐
	return psoPoolIndex_dstMapIndex.second;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///psoのアドレスを格納
void RenderContext::PSO_PoolDispatcher::Register
(
	NexusFieldProof proof_,
	uint32_t dstMapIndex_,
	const GraphicsPSO_Key& psoKey_,
	ID3D12PipelineState* graphicsPSO_
)
{
	ErrorMessageOutput::Assert::DetectError(graphicsPSO_, "psoがヌルです", fileName);

	graphicsPSO_pool.emplace_back(graphicsPSO_);

	//psoコンテナのインデックス
	uint32_t const insertedIndex = uint32_t(graphicsPSO_pool.size() - 1);
	
	//psoキーをuint32_tにパックする
	uint32_t const packedKey = PackKey(psoKey_);
	
	///insertedIndexを検索用マップに追加
	closedHashMap->Insert(dstMapIndex_, packedKey, insertedIndex);
}

size_t const RenderContext::PSO_PoolDispatcher::WatchPSO_Size()const
{
	return graphicsPSO_pool.size();
}



