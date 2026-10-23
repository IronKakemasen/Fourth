#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainContextDiplomat.h"
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainExecutionAgent/SwapChainExecutionAgent.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../LowerLayer/Core/Command/CommandContextDiplomat/CommandContextExecutionAgent/CommandContextExecutionAgent.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../MiddleLayer/Scene/SceneContextDiplomat/SceneContextDiplomat.h"
#include "../MiddleLayer/Scene/SceneContextDiplomat/SceneExecutionAgent/SceneExecutionAgent.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Buffer/BufferContext.h"

void Nexus::Run(aFourthProof proof_)
{
	//SwapChainContextの代行クラス
	auto& swap_ExecutionAgent = swapChainContext->AccessDiplomat().Access<SwapChainContext::ExecutionAgent>();
	//CommandContextの代行クラス
	auto& cmd_ExecutionAgent = commandContext->AccessDiplomat().Access<CommandContext::ExecutionAgent>();
	//SceneContextの代行クラス
	auto& scene_ExecutionAgent = sceneContext->AccessDiplomat().Access<SceneContext::ExecutionAgent>();

	//フレームインデックスをスワップチェーンから取得
	auto const frameIndex = swap_ExecutionAgent.GetFrameIndex(SwapChainContext::NexusFieldProof{});

	//シーンの更新処理、シーンデータのバッチング
	scene_ExecutionAgent.RunScenePipeline
	(
		SceneContext::NexusFieldProof{},
		frameIndex,
		modelContext->AccessDiplomat(),
		cameraContext->AccessDiplomat(),
		bufferContext->AccessDiplomat()
	);


	//コマンドの記録開始
	cmd_ExecutionAgent.StartRecordingCommands(CommandContext::NexusFieldProof{}, frameIndex);




	//コマンドを送る
	cmd_ExecutionAgent.ExecuteCommands(CommandContext::NexusFieldProof{},frameIndex);


	//表示
	swap_ExecutionAgent.Present(SwapChainContext::NexusFieldProof{});
}
