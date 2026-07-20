#include "CommandContext.h"

//ツール
#include "Synchronizer/Synchronizer.h"
#include "RuntimeWrapper/RuntimeWrapper.h"
#include "ResourceUploader/ResourceUploader.h"
#include "RuntimeCommandController/RuntimeCommandController.h"


#include "CommandContextDiplomat/CommandContextDiplomat.h"
#include "CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"
#include "CommandContextDiplomat/CommandContextToolLender/CommandContextToolLender.h"

//外部
#include "../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

using namespace ProjectConfig::Render;

namespace
{
	auto fileName = "CommandContext.cpp";
}

CommandContext::~CommandContext() {}

CommandContext::CommandContext
(
	const InstanceKey& instanceKey_,
	DeviceContextDiplomat* deviceContextDiplomat_
) 
{
	Logger::Entry("CommandContext: Constructor");

	//コアパーツの生成
	CreateCoreParts(instanceKey_, deviceContextDiplomat_);
	//フェンスイベントの生成
	CreateFenceEvent();

	synchronizer.reset(new Synchronizer(commandQueue.Get(), fence.Get(), &fenceCounters, &fenceEvent,&commonFenceValue));
	Logger::Log("Instantiate: Synchronizer", fileName);

	runtimeWrapper.reset(new RuntimeWrapper(commandList.Get()));
	Logger::Log("Instantiate: RuntimeWrapper", fileName);

	resourceUploader.reset(new ResourceUploader(instanceKey_, deviceContextDiplomat_, commandQueue.Get(), synchronizer.get()));
	Logger::Log("Instantiate: ResourceUploader", fileName);

	//ランタイムでコマンドを利用するクラスの生成
	InstantiateRuntimeCommandControler();

	diplomat.reset
	(
		new CommandContextDiplomat
		(
			instanceKey_,
			std::make_unique<CommandProvider>(instanceKey_, resourceUploader.get()),
			std::make_unique<ToolLender>(instanceKey_, commandQueue.Get())
		)
	);

	Logger::Log("Instantiate: CommandContextDiplomat", fileName);

	Logger::End("CommandContext: Constructor");
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::CreateCoreParts(InstanceKey instanceKey_ , DeviceContextDiplomat* deviceContextDiplomat_)
{
	auto* cmdExecutor = deviceContextDiplomat_->Access<DeviceContext::CommandExecutor>();

	//メイン
	auto [cmdQueue, cmdAllocators, cmdList] =
		cmdExecutor->CreateCommandContextCorePartsForRuntime(instanceKey_);

	commandQueue = std::move(cmdQueue);
	commandAllocators = std::move(cmdAllocators);
	commandList = std::move(cmdList);

	fence = std::move(cmdExecutor->CreateFence(instanceKey_));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::CreateFenceEvent()
{
	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ErrorMessageOutput::Assert::DetectError((fenceEvent != nullptr), "フェンスイベント作成失敗", fileName);
	Logger::Log("Create: FenceEvent", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::InstantiateRuntimeCommandControler()
{
	std::array<ID3D12CommandAllocator*, (UINT)NumBuffer::kDoubleBuffer> cmdAllocators;
	
	for (int i = 0;i < (UINT)NumBuffer::kDoubleBuffer;++i)
	{
		cmdAllocators.at(i) = commandAllocators.at(i).Get();
	}

	runtimeCommandController.reset
	(
		new RuntimeCommandController
		(
			commandQueue.Get(),
			cmdAllocators,
			commandList.Get(),
			synchronizer.get()
		)
	);
	Logger::Log("Instantiate: RuntimeCommandControler", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::Finalize(InstanceKey instanceKey_)
{
	synchronizer->WaitDirectly();
	CloseHandle(fenceEvent);

}



