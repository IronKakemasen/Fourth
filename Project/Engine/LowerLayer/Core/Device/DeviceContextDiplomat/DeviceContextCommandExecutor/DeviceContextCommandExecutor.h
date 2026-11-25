#pragma once
#include "../../DeviceContext.h"

class DeviceContextCommandBehavior;

//コマンドを実行するクラス
class DeviceContext::CommandExecutor
{
public:

	struct CommandContextProof;
	struct DebugContextProof;

	CommandExecutor
	(
		NexusFieldProof proof_,
		std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_
	);

	//DescriptorHeapのハンドルインクリメントサイズを返す関数
	UINT CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_);

	//フェンス生成
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence(CommandContextProof proof_);

	//CommandContextのコアパーツ生成.ランタイム用
	[[nodiscard]] std::tuple
	<
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>
	>
	CreateCommandContextCorePartsForRuntime(CommandContextProof proof_);

	//リソースアップロード用
	[[nodiscard]] std::tuple<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>>
	CreateCommandContextCorePartsForUpload(CommandContextProof proof_);

	//IMGuiの初期化関数を呼ぶ
	void CallImGuiInit
	(
		DebugContextProof proof_,
		DXGI_FORMAT format_,
		ID3D12DescriptorHeap* srvUavDescriptorHeap_,
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_,
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_
	);

private:

	//デバイスコンテキストのコアパーツにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter;
};

