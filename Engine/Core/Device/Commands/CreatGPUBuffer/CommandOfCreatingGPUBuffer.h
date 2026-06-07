#pragma once
#include "../DeviceContextCommandBehavior.h"

struct ConstantBufferDescription;
struct ColorBufferDescription;


//各Typeのバッファを作る関数群
struct CommandCreateGPUBuffer : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandGeneratorクラスのみ生成可能
	CommandCreateGPUBuffer(DeviceContext::CommandGenerator::GenerateKey generateKey_);
	~CommandCreateGPUBuffer();

	//ConstantBufferを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateConstantBuffer(ID3D12Device8* device_,
		const ConstantBufferDescription& desc_);
	//ColorBufferを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateColorBuffer(ID3D12Device8* device_, 
		const ColorBufferDescription& desc_);	

};

