#include "PreCompileHeader.h"
#include "CommandContext.h"
#include "Synchronizer/Synchronizer.h"


namespace
{
	auto fileName = "CommandContext.cpp";
}

CommandContext::~CommandContext() {}

CommandContext::CommandContext
(
	InstanceKey instanceKey_,
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_
) :commandQueue(std::move(commandQueue_)), commandAllocators(std::move(commandAllocators_)), commandList(std::move(commandList_)), fence(std::move(fence_))
{
	Logger::Entry("CommandContext: Constructor");

	CreateFenceEvent();
	Logger::Log("Create: FenceEvent", fileName);

	synchronizer.reset(new Synchronizer(commandQueue.Get(), fence.Get(), &fenceCounters, &fenceEvent));
	Logger::Log("Create: Synchronizer", fileName);


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

