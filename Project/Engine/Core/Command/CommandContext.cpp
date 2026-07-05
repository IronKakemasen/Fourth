#include "PreCompileHeader.h"
#include "CommandContext.h"

//ツール
#include "Synchronizer/Synchronizer.h"
#include "CommandExecutor/CommandExecutor.h"
#include "RuntimeWrapper/RuntimeWrapper.h"
#include "ResourceUploader/ResourceUploader.h"
#include "RuntimeCommandControler/RuntimeCommandControler.h"


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
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, kDoubleBuffer> commandAllocators_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_,
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_,
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator_forUpload_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList_forUpload_
) :commandQueue(std::move(commandQueue_)), commandAllocators(std::move(commandAllocators_)), commandList(std::move(commandList_)), fence(std::move(fence_))
{
	Logger::Entry("CommandContext: Constructor");


	CreateFenceEvent();

	synchronizer.reset(new Synchronizer(commandQueue.Get(), fence.Get(), &fenceCounters, &fenceEvent,&commonFenceValue));
	Logger::Log("Instantiate: Synchronizer", fileName);

	runtimeWrapper.reset(new RuntimeWrapper(commandList.Get()));
	Logger::Log("Instantiate: RuntimeWrapper", fileName);

	resourceUploader.reset(new ResourceUploader(std::move(allocator_forUpload_), std::move(cmdList_forUpload_), commandQueue.Get(), synchronizer.get()));
	Logger::Log("Instantiate: ResourceUploader", fileName);

	InstantiateRuntimeCommandControler();


	Logger::End("CommandContext: Constructor");
}

ID3D12CommandQueue* CommandContext::GetCommandQueue(CmdQueueGetKey key_)
{
	return commandQueue.Get();
}

void CommandContext::CreateFenceEvent()
{
	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ErrorMessageOutput::Assert::DetectError((fenceEvent != nullptr), "フェンスイベント作成失敗", fileName);
	Logger::Log("Create: FenceEvent", fileName);
}

void CommandContext::InstantiateRuntimeCommandControler()
{
	std::array<ID3D12CommandAllocator*, kDoubleBuffer> cmdAllocators;
	
	for (int i = 0;i < kDoubleBuffer;++i)
	{
		cmdAllocators.at(i) = commandAllocators.at(i).Get();
	}

	std::unique_ptr<CommandExecutor> commandExecutor(std::make_unique<CommandExecutor>(commandQueue.Get(), cmdAllocators, commandList.Get()));
	Logger::Log("Create: commandExecutor", fileName);

	runtimeCommandControler.reset(new RuntimeCommandControler(std::move(commandExecutor), synchronizer.get()));
	Logger::Log("Instantiate: RuntimeCommandControler", fileName);
}




void CommandContext::Finalize(InstanceKey instanceKey_)
{
	synchronizer->WaitDirectly();
}



