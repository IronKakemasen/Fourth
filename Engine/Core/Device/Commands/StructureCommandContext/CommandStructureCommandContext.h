#pragma once
#include "../DeviceContextCommandBehavior.h"


//CommandContextを構築するためのコマンド
//これは初期化字しか呼ばないかつ、引数がほぼないのでコマンドプロバイダーが叩くことにする
struct CommandStructureCommandContext : public DeviceContextCommandBehavior
{
	CommandStructureCommandContext(DeviceContext::CommandProvider::GenerateKey generateKey_);
	~CommandStructureCommandContext();

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue(ID3D12Device* device_);
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ID3D12Device* device_);
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> CreateCommandList
	(
		ID3D12Device* device_,
		ID3D12CommandAllocator* cmdAllocator_
	);

};

