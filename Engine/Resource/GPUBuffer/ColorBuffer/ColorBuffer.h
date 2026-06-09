#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"


class RTV_Creator;

//カラーバッファクラス
class ColorBuffer : public GPUBufferBehavior
{
public:

	ColorBuffer(const InstanceKey& instanceKey_, std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, ColorBufferDescription desc_);

	//インデックスを書き換えキー
	struct OverrideIndexKey;

	//アクセスインデックスを入力
	void OverrideIndex(OverrideIndexKey key_, uint32_t index_);
	//リソースのディスクリプションを見る
	ColorBufferDescription WatchDescription() const;

private:

	//rtvHeap上のインデックスコンテナのアクセスインデックス
	uint32_t rtvHeapIndex{};
	ColorBufferDescription desc;
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	//viewportとscissorRectをセット
	void SetMatrix();

};


//インデックスの書き換えはViewCreatorのみ可能
struct ColorBuffer::OverrideIndexKey
{
private:
	friend class RTV_Creator;

	explicit OverrideIndexKey() = default;
};
