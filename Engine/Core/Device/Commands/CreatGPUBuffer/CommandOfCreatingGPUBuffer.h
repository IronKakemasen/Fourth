#pragma once
#include "../DeviceContextCommandBehavior.h"

struct ConstantBufferDescription;
struct ColorBufferDescription;
struct SRV_UAVBufferDescription;

//各バッファのId3d12Resourceを作るコマンド群
struct CommandCreateGPUBuffer : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandGeneratorクラスのみ生成可能
	CommandCreateGPUBuffer(DeviceContext::CommandGenerator::GenerateKey generateKey_);
	~CommandCreateGPUBuffer();

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateResource
	(
		ID3D12Device8* device_,
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		const std::string& name_
	);

	//ConstantBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateConstantBuffer(ID3D12Device8* device_,
		const ConstantBufferDescription& desc_);
	//ColorBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateColorBuffer(ID3D12Device8* device_, 
		const ColorBufferDescription& desc_);	
	//SRV_UAVBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateSRV_UAVBuffer(ID3D12Device8* device_,
		const SRV_UAVBufferDescription& desc_);


private:
	//初期ステートを割り出す
	D3D12_RESOURCE_STATES ConfigureInitialResourceState(D3D12_HEAP_TYPE heapType_, D3D12_RESOURCE_FLAGS resourceFlag_);

};

