#include "PSO_PoolDispatcher.h"

//ツール
#include "Tool/GraphicsPSO_KeyPackager/GraphicsPSO_KeyPackager.h"
#include "Tool/GraphicsPSO_Index/GraphicsPSO_Index.h"


RenderContext::PSO_PoolDispatcher::PSO_PoolDispatcher
(
	RenderContext::InstacnceKey key_
)
{
	graphicsPSO_Index.reset(new GraphicsPSO_Index);
	graphicsPSO_KeyPackager.reset(new GraphicsPSO_KeyPackager);

}

RenderContext::PSO_PoolDispatcher::~PSO_PoolDispatcher()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ID3D12PipelineState* RenderContext::PSO_PoolDispatcher::AccessGraphicsPSO(DataAccessLicense license_ ,GraphicsPSO_Key key_)
{
	auto packedKey = graphicsPSO_KeyPackager->CreateKey(key_);
	uint32_t const index = graphicsPSO_Index->FindIndex(packedKey);

	return graphicsPSO_pool.at(index);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PSO_PoolDispatcher::Register(RegisterLicense license_, GraphicsPSO_Key key_, ID3D12PipelineState* graphicsPSO_)
{
	auto packedKey = graphicsPSO_KeyPackager->CreateKey(key_);
	uint32_t const index = graphicsPSO_Index->FindIndex(packedKey);

	///既に登録済みか確認
	if (index == GraphicsPSO_Index::InvalidIndex) return;

	///プールに登録
	graphicsPSO_pool.emplace_back(graphicsPSO_);

	//プールの次のインデックスを取得
	size_t const nextPoolIndex = graphicsPSO_pool.size();

	graphicsPSO_Index->Insert(packedKey, uint32_t(nextPoolIndex));
}