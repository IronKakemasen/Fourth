#pragma once
#include "../RenderContext.h"
#include "GraphicsPSO_Key.h"


class RenderContext::PSO_PoolDispatcher
{
public:

	//psoのアドレスにアクセスする許可証
	struct DataAccessLicense;
	//psoを登録するための許可証
	struct RegisterLicense;

	PSO_PoolDispatcher(RenderContext::InstacnceKey key_);
	
	~PSO_PoolDispatcher();

	///psoを渡す
	ID3D12PipelineState* AccessGraphicsPSO(DataAccessLicense license_ ,GraphicsPSO_Key key_);

	//psoのアドレスを格納
	void Register(RegisterLicense license_ , GraphicsPSO_Key key_, ID3D12PipelineState* graphicsPSO_);

private:

	//PSOキーをuint32_tに詰める
	struct GraphicsPSO_KeyPackager;
	//オープンアドレッシング・ハッシュテーブル法で、より高速にPSOを検索するためのツール
	//poolの中の目的のPSOのインデックスを取得する
	class GraphicsPSO_Index;

	std::unique_ptr<GraphicsPSO_KeyPackager> graphicsPSO_KeyPackager;
	std::unique_ptr<GraphicsPSO_Index> graphicsPSO_Index;

	///プール本体
	std::vector<ID3D12PipelineState*> graphicsPSO_pool;

};

struct RenderContext::PSO_PoolDispatcher::DataAccessLicense
{
private:
	///未登録

	explicit DataAccessLicense() = default;

};

struct RenderContext::PSO_PoolDispatcher::RegisterLicense
{
private:
	friend class RenderContext::PSO_Creator;
	explicit RegisterLicense() = default;

};
