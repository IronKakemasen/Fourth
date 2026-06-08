#pragma once
#include "../DescriptorHeapContext.h"

class DescriptorHeapClass
{
public:
	DescriptorHeapClass(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
		UINT handleIncrementSize_, uint32_t kMaxDescriptor_);

private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//ハンドルのインクリメントサイズ
	UINT handleIncrementSize{};
	//最大領域分割数
	uint32_t kMaxDescriptor{};
};

