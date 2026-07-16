#pragma once
#include "../DeviceContext.h"

class DeviceContextCommandBehavior;

//コマンドを実行するクラス
class DeviceContext::CommandExecutor
{
public:

	CommandExecutor
	(
		DeviceContext::InstanceKey instanceKey_,
		std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_
	);

	//DescriptorHeapのハンドルインクリメントサイズを返す関数
	UINT CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_);

	//フェンス生成
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence();

	//CommandContextのコアパーツ生成.ランタイム用
	[[nodiscard]] std::tuple
	<
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>
	>
	CreateCommandContextCorePartsForRuntime(DeviceContext::InstanceKey instanceKey_);

	//リソースアップロード用
	[[nodiscard]] std::tuple<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>>
	CreateCommandContextCorePartsForUpload(DeviceContext::InstanceKey instanceKey_);


private:

	//デバイスコンテキストのコアパーツにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter;
};

