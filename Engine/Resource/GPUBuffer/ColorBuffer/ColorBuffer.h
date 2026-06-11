#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"


//カラーバッファクラス
class ColorBuffer : public GPUBufferBehavior
{
public:

	ColorBuffer(const InstanceKey& instanceKey_, std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, ColorBufferDescription desc_);


	//アクセスインデックスを入力(SRV / RTV)
	template<ViewType viewType>
	void OverrideIndex(OverrideIndexKey key_, uint32_t index_);

	//リソースのディスクリプションを見る
	ColorBufferDescription WatchDescription() const;

private:

	//rtvHeap上のインデックスコンテナのアクセスインデックス
	uint32_t rtvContainerIndex{};
	//そのsrv
	uint32_t srvHeapIndex{};

	//ディスクリプション
	ColorBufferDescription desc;

	//行列
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	//viewportとscissorRectをセット
	void SetMatrix();
};



