#pragma once

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
	//リソースのアップロードを行う
	class ResourceUploader;

public:

	struct InstanceKey;
	//コマンドキューのアドレス取得キー
	struct CmdQueueGetKey;
	//ResourceUploaderの利用許可
	struct UsesResourceUploaderPermission;

	CommandContext
	(
		InstanceKey instanceKey_,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kDoubleBuffer> commandAllocators_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_,
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator_forUpload_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList_forUpload_
	);

	~CommandContext();

	ID3D12CommandQueue* GetCommandQueue(CmdQueueGetKey key_);
	ResourceUploader* GetResourceUploader();

	void Finalize(InstanceKey instanceKey_);

	std::unique_ptr<RuntimeCommandController> runtimeCommandController;

private:

	std::unique_ptr<Synchronizer> synchronizer;
	std::unique_ptr<RuntimeWrapper> runtimeWrapper;
	std::unique_ptr<ResourceUploader> resourceUploader;

	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//コマンドアローケータ
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>,ProjectConfig::Render::kDoubleBuffer> commandAllocators;
	//コマンドリスト		
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	//カウンタ
	uint64_t commonFenceValue = 0;
	//それぞれのカウンタ
	std::array<uint64_t,ProjectConfig::Render::kDoubleBuffer> fenceCounters = { 0,0 };
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

struct CommandContext::UsesResourceUploaderPermission
{
private:


	explicit UsesResourceUploaderPermission() = default;
};

