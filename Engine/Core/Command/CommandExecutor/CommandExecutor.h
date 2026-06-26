#pragma once
#include "../CommandContext.h"

class CommandContext::CommandExecutor
{
public:
	CommandExecutor
	(
		ID3D12CommandQueue* commandQueue_,
		std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kDoubleBuffer> commandAllocators_,
		ID3D12GraphicsCommandList6* commandList_
	);

	//アロケーターとコマンドリストをリセットする
	void PrepareForRecording(UINT frameIndex_);
	//コマンドを確定する
	void Execute();

private:

	ID3D12CommandQueue* commandQueue;
	std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kDoubleBuffer> commandAllocators;
	ID3D12GraphicsCommandList6* commandList;
};

