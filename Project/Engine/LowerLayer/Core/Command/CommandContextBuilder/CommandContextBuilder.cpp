#include "PreCompileHeader.h"
#include "CommandContextBuilder.h"
#include "../RuntimeCommandController/RuntimeCommandController.h"

//外部
#include "../../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"


namespace
{
	auto fileName = "CommandContextBuilder.cpp";
}

using namespace ProjectConfig::Render;

CommandContext::Builder::Output CommandContext::Builder::CreateCoreParts
(
	NexusFieldProof proof_,
	DeviceContextDiplomat& deviceContextDiplomat_
)
{
	Output output;

	//deviceContextのCmdExecutorにアクセス
	auto* cmdExecutor = deviceContextDiplomat_.Access<DeviceContext::CommandExecutor>();

	//フェンス作成
	output.fence = std::move(cmdExecutor->CreateFence(proof_));

	//フェンスイベント作成
	output.fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ErrorMessageOutput::Assert::DetectError((output.fenceEvent != nullptr), "フェンスイベント作成失敗", fileName);
	Logger::Log("Create: FenceEvent", fileName);


	//コアパーツ作成
	auto [cmdQueue, cmdAllocators, cmdList] = cmdExecutor->CreateCommandContextCorePartsForRuntime(proof_);

	output.commandQueue = std::move(cmdQueue);
	output.commandAllocators = std::move(cmdAllocators);
	output.commandList = std::move(cmdList);


	////runtimeCommandControllerの生成
	//std::array<ID3D12CommandAllocator*, (UINT)NumBuffer::kDoubleBuffer> cmdAllocators;

	//for (int i = 0;i < (UINT)NumBuffer::kDoubleBuffer;++i)
	//{
	//	cmdAllocators.at(i) = output.commandAllocators.at(i).Get();
	//}

	//output.runtimeCommandController = std::make_unique<RuntimeCommandController>
	//(
	//	output.commandQueue.Get(),
	//	cmdAllocators,
	//	output.commandList.Get(),
	//	synchronizer
	//);

	//Logger::Log("Instantiate: RuntimeCommandController", fileName);

	return std::move(output);
}
