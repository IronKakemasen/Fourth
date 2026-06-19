#pragma once

class Nexus;
class SwapChainContext;
class ResourceUploader;

class CommandContext
{
public:

	struct InstanceKey;
	//コマンドキューのアドレス取得キー
	struct CmdQueueGetKey;
	struct CloseKey;

	CommandContext
	(
		InstanceKey instanceKey_,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_,
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator_forUpload_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList_forUpload_
	);

	~CommandContext();

	ID3D12CommandQueue* GetCommandQueue(CmdQueueGetKey accessKey_);

	//コマンド記録スタート
	void RecordingStart(UINT frameIndex_);
	//コマンドを送り待つ
	void ExecuteCommands(UINT frameIndex_);
	//初期化処理終了時に強制的にコマンドを閉じる
	void CloseBeforeRun(InstanceKey instanceKey_);

	void Finalize(InstanceKey instanceKey_);

private:

	//FenceでCPUとGPUを同期させる
	class Synchronizer;
	//コマンドを実行する
	class CommandExecutor;
	//コマンドリストの処理のラッパークラス
	class RuntimeWrapper;
	//リソースのアップロードを行う
	class ResourceUploader;

	std::unique_ptr<Synchronizer> synchronizer;
	std::unique_ptr<CommandExecutor> commandExecutor;
	std::unique_ptr<RuntimeWrapper> runtimeWrapper;
	std::unique_ptr<ResourceUploader> resourceUploader;

	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//コマンドアローケータ
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>,ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators;
	//コマンドリスト		
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;

	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	//カウンタ
	std::array<uint64_t,ProjectConfig::Render::kRequiredGPUBufferSum> fenceCounters = { 0,0 };
	//フェンスイベント
	HANDLE fenceEvent = nullptr;
	uint64_t commonFenceValue = 0;


	void CreateFenceEvent();
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

struct CommandContext::CloseKey
{
	friend class CommandContext;
	explicit CloseKey() = default;

};