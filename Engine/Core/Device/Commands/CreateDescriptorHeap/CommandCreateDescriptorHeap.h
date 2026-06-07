#pragma once

#include "../DeviceContextCommandBehavior.h"


//DescriptorHeapを生成するコマンド
struct CommandCreateDescriptorHeap  : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandGeneratorクラスのみ生成可能
	CommandCreateDescriptorHeap(DeviceContext::CommandGenerator::GenerateKey generateKey_);
	~CommandCreateDescriptorHeap();


	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> Create(ID3D12Device* device_,
		D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible);
};

