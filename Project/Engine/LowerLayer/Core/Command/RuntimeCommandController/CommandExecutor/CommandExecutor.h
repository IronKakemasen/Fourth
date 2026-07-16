#pragma once
#include "../RuntimeCommandController.h"

class CommandContext::RuntimeCommandController::CommandExecutor
{
public:
	CommandExecutor
	(
		ID3D12CommandQueue* commandQueue_,
		std::array<ID3D12CommandAllocator*, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators_,
		ID3D12GraphicsCommandList6* commandList_
	);

	//アロケーターとコマンドリストをリセットする
	void PrepareForRecording(UINT frameIndex_);
	//コマンドを確定する
	void Execute();

private:

	ID3D12CommandQueue* commandQueue;
	std::array<ID3D12CommandAllocator*, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators;
	ID3D12GraphicsCommandList6* commandList;
};

