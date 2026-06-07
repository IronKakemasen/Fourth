#pragma once
#include "../DescriptorHeapContext.h"


class DescriptorHeapContext::DescriptorHeapCreator
{
public:

	std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> createFunc;

	DescriptorHeapCreator(DescriptorHeapContext::InstanceKey instanceKey_);
	~DescriptorHeapCreator();

	void SetCommand(std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> func_);
};

