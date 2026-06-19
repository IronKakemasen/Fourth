#include "PreCompileHeader.h"
#include "CommandContext.h"
#include "Synchronizer/Synchronizer.h"
#include "CommandExecutor/CommandExecutor.h"
#include "RuntimeWrapper/RuntimeWrapper.h"
#include "ResourceUploader/ResourceUploader.h"


using namespace ProjectConfig::Render;

namespace
{
	auto fileName = "CommandContext.cpp";
}

CommandContext::~CommandContext() {}

CommandContext::CommandContext
(
	InstanceKey instanceKey_,
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, kRequiredGPUBufferSum> commandAllocators_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_,
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator_forUpload_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList_forUpload_
) :commandQueue(std::move(commandQueue_)), commandAllocators(std::move(commandAllocators_)), commandList(std::move(commandList_)), fence(std::move(fence_))
{
	Logger::Entry("CommandContext: Constructor");

	{
		CreateFenceEvent();
		Logger::Log("Create: FenceEvent", fileName);
	}

	{
		synchronizer.reset(new Synchronizer(commandQueue.Get(), fence.Get(), &fenceCounters, &fenceEvent,&commonFenceValue));
		Logger::Log("Instantiate: Synchronizer", fileName);
	}

	{
		std::array<ID3D12CommandAllocator*, kRequiredGPUBufferSum> cmdAllocators;
		for (int i = 0;i < kRequiredGPUBufferSum;++i)
		{
			cmdAllocators.at(i) = commandAllocators.at(i).Get();
		}
		commandExecutor.reset(new CommandExecutor(commandQueue.Get(), cmdAllocators, commandList.Get()));
		Logger::Log("Instantiate: commandExecutor", fileName);
	}

	{
		runtimeWrapper.reset(new RuntimeWrapper(commandList.Get()));
		Logger::Log("Instantiate: RuntimeWrapper", fileName);
	}

	{
		resourceUploader.reset(new ResourceUploader(std::move(allocator_forUpload_), std::move(cmdList_forUpload_), commandQueue.Get(), synchronizer.get()));
		Logger::Log("Instantiate: ResourceUploader", fileName);
	}


	Logger::End("CommandContext: Constructor");
}

ID3D12CommandQueue* CommandContext::GetCommandQueue(CmdQueueGetKey getKey_)
{
	return commandQueue.Get();
}

void CommandContext::CreateFenceEvent()
{
	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ErrorMessageOutput::Assert::DetectError((fenceEvent != nullptr), "フェンスイベント作成失敗", fileName);
}

void CommandContext::RecordingStart(UINT frameIndex_)
{
	synchronizer->Wait(frameIndex_);
	commandExecutor->PrepareForRecording(frameIndex_);
}

void CommandContext::ExecuteCommands(UINT frameIndex_)
{
	commandExecutor->Execute();
	synchronizer->InsertSignal(frameIndex_);
}

void CommandContext::CloseBeforeRun(InstanceKey instanceKey_)
{

	commandExecutor->Close(CloseKey{});
	resourceUploader->Close(CloseKey{});
	Logger::Log("Close: CmdList", fileName);

}

void CommandContext::Finalize(InstanceKey instanceKey_)
{
	synchronizer->WaitDirectly();
}



