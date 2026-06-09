#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"



//カラーバッファクラス
class ColorBuffer : public GPUBufferBehavior
{
public:

	ColorBuffer(const InstanceKey& instanceKey_, std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, ColorBufferDescription desc_);

	//インデックスを書き換えキー
	struct IndexOverrideKey;


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
struct ColorBuffer::IndexOverrideKey
{
private:
	friend class ViewCreatorBahevior;

	explicit IndexOverrideKey() = default;
};
