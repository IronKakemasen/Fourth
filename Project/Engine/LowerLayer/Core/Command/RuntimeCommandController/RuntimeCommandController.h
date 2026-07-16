#pragma once
#include "../Synchronizer/Synchronizer.h"


class CommandContext::RuntimeCommandController
{
	//コマンドを実行する
	class CommandExecutor;

public:

	RuntimeCommandController
	(
		ID3D12CommandQueue* commandQueue_,
		std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kDoubleBuffer> commandAllocators_,
		ID3D12GraphicsCommandList6* commandList_,
		Synchronizer* synchronizer_
	);

	~RuntimeCommandController();

	void RecordingStart(UINT frameIndex_);
	void ExecuteCommands(UINT frameIndex_);

private:
	std::unique_ptr<CommandExecutor> commandExecutor;
	Synchronizer* synchronizer;
};

