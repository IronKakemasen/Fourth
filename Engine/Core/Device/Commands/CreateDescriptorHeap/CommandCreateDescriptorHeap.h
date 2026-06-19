#pragma once

#include "../DeviceContextCommandBehavior.h"


//DescriptorHeapを生成するコマンド
struct CommandCreateDescriptorHeap  : public DeviceContextCommandBehavior
{
	CommandCreateDescriptorHeap(DeviceContext::GenerateKey generateKey_);
	~CommandCreateDescriptorHeap();


	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> Create(ID3D12Device8* device_,
		D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible);
};

