#pragma once
#include "../Synchronizer/Synchronizer.h"
#include "../CommandExecutor/CommandExecutor.h"

class CommandContext::RuntimeCommandControler
{
public:

	RuntimeCommandControler(std::unique_ptr<CommandExecutor>&& commandExecutor_, Synchronizer* synchronizer_);
	~RuntimeCommandControler();

	void RecordingStart(UINT frameIndex_);
	void ExecuteCommands(UINT frameIndex_);

private:
	std::unique_ptr<CommandExecutor> commandExecutor;
	Synchronizer* synchronizer;
};

