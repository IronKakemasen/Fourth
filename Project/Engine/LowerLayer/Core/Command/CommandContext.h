#pragma once
#include "../../Resource/Buffer/BufferContext.h"

class Nexus;
class SwapChainContext;

class CommandContext
{
	//ランタイムでのコマンド制御を行う
	class RuntimeCommandController;
	//FenceでCPUとGPUを同期させる
	class Synchronizer;
	//コマンドリストの処理のラッパークラス
	class RuntimeWrapper;

public:

	using UploadCommand = std::function<void
	(
		ID3D12Resource* dstResource_,
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)>;


	struct InstanceKey;
	//コマンドキューのアドレス取得キー
	struct CmdQueueGetKey;
	//リソースのアップロードを行う
	class ResourceUploader;
	//コマンドを提供する
	class CommandProvider;

	CommandContext
	(
		const InstanceKey& instanceKey_,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_,
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator_forUpload_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList_forUpload_
	);

	~CommandContext();

	//コマンドキューの取得
	ID3D12CommandQueue* GetCommandQueue(CmdQueueGetKey key_);
	//同期してCloseHandle()する
	void Finalize(InstanceKey instanceKey_);

	std::unique_ptr<RuntimeCommandController> runtimeCommandController;
	std::unique_ptr<ResourceUploader> resourceUploader;
	std::unique_ptr<CommandProvider> commandProvider;

private:

	std::unique_ptr<Synchronizer> synchronizer;
	std::unique_ptr<RuntimeWrapper> runtimeWrapper;

	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//コマンドアローケータ
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators;
	//コマンドリスト		
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	//カウンタ
	uint64_t commonFenceValue = 0;
	//それぞれのカウンタ
	std::array<uint64_t,(UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> fenceCounters = { 0,0 };
	//フェンスイベント
	HANDLE fenceEvent = nullptr;

	void CreateFenceEvent();
	void InstantiateRuntimeCommandControler();

};


struct CommandContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

struct CommandContext::CmdQueueGetKey
{
private:

	friend class Nexus;
	friend class SwapChainContext;
	explicit CmdQueueGetKey() = default;

};

