#include "PSO_PoolDispatcher.h"


namespace
{
	auto const fileName = "PSO_PoolDispatcher.cpp";
}


RenderContext::PSO_PoolDispatcher::PSO_PoolDispatcher
(
	RenderContext::InstacnceKey key_
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
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kDepthEnable>(),
			GraphicsPSO_Key::Count<GraphicsPSO_Key::Sequence::kDepthTest>(),
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
	RegisterLicense license_, 
	uint32_t dstMapIndex_,
	uint32_t packedKey_ ,
	ID3D12PipelineState* graphicsPSO_
)
{
	ErrorMessageOutput::Assert::DetectError(graphicsPSO_, "psoがヌルです", fileName);

	graphicsPSO_pool.emplace_back(graphicsPSO_);

	uint32_t const insertedIndex = uint32_t(graphicsPSO_pool.size() - 1);
	
	///insertedIndexを検索用マップに追加
	closedHashMap->Insert(dstMapIndex_, packedKey_, insertedIndex);

}










//void RenderContext::PSO_PoolDispatcher::Register(RegisterLicense license_, GraphicsPSO_Key key_, ID3D12PipelineState* graphicsPSO_)
//{
//	//auto packedKey = graphicsPSO_KeyPackager->CreateKey(key_);
//	//uint32_t const index = graphicsPSO_Index->FindIndex(packedKey);
//
//	/////既に登録済みか確認
//	//if (index == GraphicsPSO_Index::InvalidIndex) return;
//
//	/////プールに登録
//	//graphicsPSO_pool.emplace_back(graphicsPSO_);
//
//	////プールの次のインデックスを取得
//	//size_t const nextPoolIndex = graphicsPSO_pool.size();
//
//	//graphicsPSO_Index->Insert(packedKey, uint32_t(nextPoolIndex));
//}
//
