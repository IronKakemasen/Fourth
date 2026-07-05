#pragma once
#include "../DeviceContextCommandBehavior.h"


//DescriptorHeapを生成するコマンド
struct CommandCreateFenceObject : public DeviceContextCommandBehavior
{
	CommandCreateFenceObject(DeviceContext::GenerateKey generateKey_);
	~CommandCreateFenceObject();

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> CreateFenceObj(ID3D12Device8* device_);
};

