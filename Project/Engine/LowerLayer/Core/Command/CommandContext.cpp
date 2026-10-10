#include "CommandContext.h"

//ツール
#include "Synchronizer/Synchronizer.h"
#include "RuntimeWrapper/RuntimeWrapper.h"
#include "ResourceUploader/ResourceUploader.h"
#include "RuntimeCommandController/RuntimeCommandController.h"
#include "CommandContextBuilder/CommandContextBuilder.h"

#include "CommandContextDiplomat/CommandContextDiplomat.h"
#include "CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"
#include "CommandContextDiplomat/CommandContextToolLender/CommandContextToolLender.h"
#include "CommandContextDiplomat/CommandContextExecutionAgent/CommandContextExecutionAgent.h"

using namespace ProjectConfig::Render;

namespace
{
	auto fileName = "CommandContext.cpp";
}

CommandContext::~CommandContext() {}

CommandContext::CommandContext
(
	NexusFieldProof proof_,
	DeviceContextDiplomat& deviceContextDiplomat_
) 
{
	Logger::Entry("CommandContext: Constructor");

	//コアパーツの生成
	auto buildOutput = Builder::CreateCoreParts(proof_, deviceContextDiplomat_);
	fence = std::move(buildOutput.fence);
	fenceEvent = buildOutput.fenceEvent;
	commandList = std::move(buildOutput.commandList);
	commandAllocators = std::move(buildOutput.commandAllocators);
	commandQueue = std::move(buildOutput.commandQueue);


	synchronizer.reset(new Synchronizer(commandQueue.Get(), fence.Get(), &fenceCounters, &fenceEvent,&commonFenceValue));
	Logger::Log("Instantiate: Synchronizer", fileName);

	runtimeWrapper.reset(new RuntimeWrapper(commandList.Get()));
	Logger::Log("Instantiate: RuntimeWrapper", fileName);

	resourceUploader.reset(new ResourceUploader(proof_, deviceContextDiplomat_, commandQueue.Get(), synchronizer.get()));
	Logger::Log("Instantiate: ResourceUploader", fileName);

	//ランタイムでコマンドを利用するクラスの生成
	InstantiateRuntimeCommandControler();

	diplomat = std::make_unique<CommandContextDiplomat>
	(
		proof_,
		std::make_unique<CommandProvider>(proof_, resourceUploader.get()),
		std::make_unique<ToolLender>(proof_, commandQueue.Get(), runtimeWrapper.get()),
		std::make_unique<ExecutionAgent>(proof_, resourceUploader.get())
	);

	Logger::Log("Instantiate: CommandContextDiplomat", fileName);

	Logger::End("CommandContext: Constructor");
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
			*synchronizer
		)
	);
	Logger::Log("Instantiate: RuntimeCommandController", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::Finalize(NexusFieldProof proof_)
{
	synchronizer->WaitDirectly();
	CloseHandle(fenceEvent);
}



