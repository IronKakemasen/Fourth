#pragma once
#include "../DeviceContextCommandBehavior.h"

//各バッファのId3d12Resourceを作るコマンド群
struct CommandCreateResource : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandCreateResource(DeviceContext::GenerateKey generateKey_);

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateResource
	(
		ID3D12Device8* device_,
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	);

};

