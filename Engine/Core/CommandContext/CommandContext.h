#pragma once

class Nexus;
class SwapChainContext;


class CommandContext
{
public:

	struct InstanceKey;
	//コマンドキューのアドレス取得キー
	struct CmdQueueGetKey;

	CommandContext
	(
		InstanceKey instanceKey_,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_
	);

	~CommandContext();

	ID3D12CommandQueue* GetCommandQueue(CmdQueueGetKey accessKey_);

private:

	//FenceでCPUとGPUを同期させる
	class Synchronizer;


	std::unique_ptr<Synchronizer> synchronizer;

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