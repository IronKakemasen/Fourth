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

	//ConstantBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateConstantBuffer(ID3D12Device8* device_,
		const ConstantBufferDescription& desc_);
	//ColorBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateColorBuffer(ID3D12Device8* device_, 
		const ColorBufferDescription& desc_);	
	//SRV_UAVBufferのリソースを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateSRV_UAVBuffer(ID3D12Device8* device_,
		const SRV_UAVBufferDescription& desc_);
};

