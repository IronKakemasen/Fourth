#pragma once

class WinApp;
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
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_
	);

	ID3D12CommandQueue* GetCommandQueue(CmdQueueGetKey accessKey_);

private:

	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//コマンドアローケータ
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>,ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators;
	//コマンドリスト		
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;

};


struct CommandContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};

struct CommandContext::CmdQueueGetKey
{
private:

	friend class SwapChainContext;
	explicit CmdQueueGetKey() = default;

};