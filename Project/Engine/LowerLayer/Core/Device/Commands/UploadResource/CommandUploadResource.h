#pragma once
#include "../DeviceContextCommandBehavior.h"


//リソースをアップロードするためのもの
struct CommandUploadResource : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandUploadResource(DeviceContext::GenerateKey generateKey_);
	~CommandUploadResource();

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

