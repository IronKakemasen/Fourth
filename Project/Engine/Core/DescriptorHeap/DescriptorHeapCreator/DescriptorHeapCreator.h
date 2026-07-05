#pragma once
#include "../DescriptorHeapContext.h"


class DescriptorHeapContext::DescriptorHeapCreator
{
public:

	//DescriptorHeapを生成するコマンド
	std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> createFunc;

	//コマンドをセットする
	void SetCommand(std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> func_);

	DescriptorHeapCreator(DescriptorHeapContext::InstanceKey instanceKey_);
	~DescriptorHeapCreator();

};

