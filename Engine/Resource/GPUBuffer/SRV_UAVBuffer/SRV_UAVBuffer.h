#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/SRV_UAVBufferDescription/SRV_UAVBufferDescription.h"



//StructuredBuffer（読み込み専用やRWStructuredBuffer（読み書き汎用）リソース
class SRV_UAVBuffer : public GPUBufferBehavior
{
public:

	SRV_UAVBuffer(const InstanceKey& instanceKey_, std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, SRV_UAVBufferDescription desc_);

	//絶対インデックスを入力(SRV / UAV)
	template<ViewType viewType>
	void OverrideIndex(OverrideIndexKey key_, uint32_t index_);

private:
	SRV_UAVBufferDescription desc;

	//SRV_UAV_DescriptorHeap上の絶対インデックス
	uint32_t srvHeapIndex{};
	uint32_t uavHeapIndex{};

};

