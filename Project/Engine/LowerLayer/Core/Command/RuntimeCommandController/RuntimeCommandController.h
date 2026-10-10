#pragma once
#include "../CommandContext.h"


class CommandContext::RuntimeCommandController
{
	//コマンドを実行する
	class CommandExecutor;

public:

	RuntimeCommandController
	(
		NexusFieldProof proof_,
		ID3D12CommandQueue* commandQueue_,
		std::array<ID3D12CommandAllocator*, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators_,
		ID3D12GraphicsCommandList6* commandList_,
		Synchronizer& synchronizer_
	);

	~RuntimeCommandController();

	void RecordingStart(UINT frameIndex_);
	void ExecuteCommands(UINT frameIndex_);

private:
	std::unique_ptr<CommandExecutor> commandExecutor;
	Synchronizer& synchronizer;
};

