#pragma once
#include "../CommandContext.h"

class CommandContext::CommandExecutor
{
public:
	CommandExecutor
	(
		ID3D12CommandQueue* commandQueue_,
		std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators_,
		ID3D12GraphicsCommandList6* commandList_
	);

	//アロケーターとコマンドリストをリセットする
	void PrepareForRecording(UINT frameIndex_);
	//コマンドを確定する
	void Execute();

	void Close(CommandContext::CloseKey key_);
private:

	ID3D12CommandQueue* commandQueue;
	std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators;
	ID3D12GraphicsCommandList6* commandList;
};

