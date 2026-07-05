
#include "RuntimeCommandControler.h"

CommandContext::RuntimeCommandControler::RuntimeCommandControler(std::unique_ptr<CommandExecutor>&& commandExecutor_, Synchronizer* synchronizer_)
	:commandExecutor(std::move(commandExecutor_)), synchronizer(synchronizer_)
{

}

CommandContext::RuntimeCommandControler::~RuntimeCommandControler()
{

}


void CommandContext::RuntimeCommandControler::RecordingStart(UINT frameIndex_)
{
	synchronizer->Wait(frameIndex_);
	commandExecutor->PrepareForRecording(frameIndex_);
}

void CommandContext::RuntimeCommandControler::ExecuteCommands(UINT frameIndex_)
{
	commandExecutor->Execute();
	synchronizer->InsertSignal(frameIndex_);
}
