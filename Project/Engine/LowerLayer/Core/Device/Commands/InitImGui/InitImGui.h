#pragma once
#include "../DeviceContextCommandBehavior.h"

struct InitImGui : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	InitImGui(DeviceContext::GenerateKey generateKey_);

	void ImplDX12Init
	(
		ID3D12Device8* device_,
		DXGI_FORMAT format_,
		ID3D12DescriptorHeap* srvUavDescriptorHeap_,
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_,
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_
	);
};

