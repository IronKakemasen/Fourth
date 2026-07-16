#include "CommandExecutor.h"

namespace
{
	auto fileName = "CommandExecutor.cpp";
}


CommandContext::RuntimeCommandController::CommandExecutor::CommandExecutor
(
	ID3D12CommandQueue* commandQueue_,
	std::array<ID3D12CommandAllocator*, ProjectConfig::Render::kDoubleBuffer> commandAllocators_,
	ID3D12GraphicsCommandList6* commandList_
):commandQueue(commandQueue_), commandAllocators(commandAllocators_), commandList(commandList_)
{
	commandList->Close();
	Logger::Log("Close: Main CommandList", fileName);
}


void CommandContext::RuntimeCommandController::CommandExecutor::PrepareForRecording(UINT frameIndex_)
{
	HRESULT hr = commandAllocators[frameIndex_]->Reset();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドアロケーターのリセットに失敗", fileName);

	hr = commandList->Reset(commandAllocators[frameIndex_], nullptr);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドリストのリセットに失敗", fileName);

}

void CommandContext::RuntimeCommandController::CommandExecutor::Execute()
{
	//コマンドリストの内容を確定させる
	HRESULT hr = commandList->Close();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンド確定できない", fileName);

	ID3D12CommandList* commandLists[] = { commandList };
	commandQueue->ExecuteCommandLists(1, commandLists);
}

