#pragma once
#include "../../DeviceContext.h"
#include "../../../Command/CommandContext.h"

class DeviceContextCommandBehavior;

//コマンドを実行するクラス
class DeviceContext::CommandExecutor
{
public:

	CommandExecutor
	(
		NexusFieldProof proof_,
		std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_
	);

	//DescriptorHeapのハンドルインクリメントサイズを返す関数
	UINT CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_);

	//フェンス生成
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence(CommandContext::NexusFieldProof proof_);

	//CommandContextのコアパーツ生成.ランタイム用
	[[nodiscard]] std::tuple
	<
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>
	>
	CreateCommandContextCorePartsForRuntime(CommandContext::NexusFieldProof proof_);

	//リソースアップロード用
	[[nodiscard]] std::tuple<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>>
	CreateCommandContextCorePartsForUpload(CommandContext::NexusFieldProof proof_);


private:

	//デバイスコンテキストのコアパーツにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter;
};

