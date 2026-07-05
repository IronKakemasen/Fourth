#pragma once
#include "../DeviceContextCommandBehavior.h"


//CommandContextを構築するためのコマンド
//これは初期化字しか呼ばないかつ、引数がほぼないのでコマンドプロバイダーが叩くことにする
struct CommandStructureCommandContext : public DeviceContextCommandBehavior
{
	CommandStructureCommandContext(DeviceContext::GenerateKey generateKey_);
	~CommandStructureCommandContext();

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue
	(
		ID3D12Device* device_,
		D3D12_COMMAND_LIST_TYPE type_
	);

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator
	(
		ID3D12Device* device_,
		D3D12_COMMAND_LIST_TYPE type_
	);

	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> CreateCommandList
	(
		ID3D12Device* device_,
		ID3D12CommandAllocator* cmdAllocator_,
		D3D12_COMMAND_LIST_TYPE type_
	);

};

