#include "RuntimeCommandController.h"
#include"CommandExecutor/CommandExecutor.h"
#include "../Synchronizer/Synchronizer.h"

CommandContext::RuntimeCommandController::RuntimeCommandController
(
	NexusFieldProof proof_,
	ID3D12CommandQueue* commandQueue_,
	std::array<ID3D12CommandAllocator*, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators_,
	ID3D12GraphicsCommandList6* commandList_,
	Synchronizer& synchronizer_
)
	:synchronizer(synchronizer_)
{

	commandExecutor = std::make_unique<CommandExecutor>(proof_,commandQueue_, commandAllocators_, commandList_);
	Logger::Log("Create: commandExecutor", "RuntimeCommandController.cpp");


}

CommandContext::RuntimeCommandController::~RuntimeCommandController()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::RuntimeCommandController::RecordingStart(NexusFieldProof proof_, AgentKey key_, UINT frameIndex_)
{
	synchronizer.Wait(frameIndex_);
	commandExecutor->PrepareForRecording(frameIndex_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::RuntimeCommandController::ExecuteCommands(NexusFieldProof proof_, AgentKey key_, UINT frameIndex_)
{
	commandExecutor->Execute();
	synchronizer.InsertSignal(frameIndex_);
}
