
#include "RuntimeCommandController.h"

CommandContext::RuntimeCommandController::RuntimeCommandController(std::unique_ptr<CommandExecutor>&& commandExecutor_, Synchronizer* synchronizer_)
	:commandExecutor(std::move(commandExecutor_)), synchronizer(synchronizer_)
{

}

CommandContext::RuntimeCommandController::~RuntimeCommandController()
{

}


void CommandContext::RuntimeCommandController::RecordingStart(UINT frameIndex_)
{
	synchronizer->Wait(frameIndex_);
	commandExecutor->PrepareForRecording(frameIndex_);
}

void CommandContext::RuntimeCommandController::ExecuteCommands(UINT frameIndex_)
{
	commandExecutor->Execute();
	synchronizer->InsertSignal(frameIndex_);
}
