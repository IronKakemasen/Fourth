#pragma once
#include "../RenderContext.h"
#include "GraphicsPSO_Key.h"

//ツール
#include "ClosedHashMap/ClosedHashMap.h" 
#include "KeyPackager/KeyPackager.h" 


class RenderContext::PSO_PoolDispatcher
{
	//パッキング
	inline uint32_t PackKey(const GraphicsPSO_Key& psoKey_) const
	{
		return keyPackager->Pack
		(
			psoKey_.Get<GraphicsPSO_Key::Sequence::kPass>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kDepthEnable>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kDepthTest>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kMeshType>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kMaterialType>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kBlendMode>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::KFillMode>(),
			psoKey_.Get<GraphicsPSO_Key::Sequence::kCullMode>()
		);
	}

public:

	//psoのアドレスにアクセスする許可証
	struct DataAccessLicense;
	//psoを登録するための許可証
	struct RegisterLicense;

	PSO_PoolDispatcher(NexusFieldProof proof_);
	~PSO_PoolDispatcher();

	///キーをもとにpsoを検索して渡す
	[[nodiscard]] inline ID3D12PipelineState* AccessGraphicsPSO(const DataAccessLicense& license_, const GraphicsPSO_Key& key_)const
	{
		uint32_t const packedKey = PackKey(key_);
		uint32_t const psoPoolIndex = closedHashMap->FindValueFast(packedKey);

		return graphicsPSO_pool.at(psoPoolIndex);
	}

	///作成予定のPSOが既に存在していたらそのアドレスを返し、
	///存在していなければ、挿入すべきインデックスを返す
	[[nodiscard]] std::optional<uint32_t> CheckDuplication(const GraphicsPSO_Key& psoKey_);

	///psoのアドレスを格納
	///CheckDuplicationが返すインデックスを引数へ
	void Register
	(
		RegisterLicense license_,
		uint32_t dstMapIndex_,
		uint32_t packedKey_,
		ID3D12PipelineState* graphicsPSO_
	);

private:

	//PSOキーをuint32_tに詰める
	std::unique_ptr<KeyPackager> keyPackager;
	//poolの中の目的のPSOのインデックスを高速に取得する
	std::unique_ptr<ClosedHashMap<uint32_t>> closedHashMap;

	///プール本体
	std::vector<ID3D12PipelineState*> graphicsPSO_pool;
	//closedHashMapのキャパ。想定されるPSOの数がキャパの4割位未満を目安
	const uint32_t kHashMapCapacity = 2048;

	//closedHashMapのビットレイアウトを定める
	void DefinePackageLayout();
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
