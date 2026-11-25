#include "Nexus.h"

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/DescriptorHeap/DescriptorHeapContext.h"
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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../MiddleLayer/Render/RenderContextDiplomat/RenderContextDiplomat.h"
#include "../MiddleLayer/Render/RenderContextDiplomat/RenderContextExecutionAgent/RenderContextExecutionAgent.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/DebugSystem/DebugContextDiplomat/DebugContextDiplomat.h"
#include "../LowerLayer/DebugSystem/DebugContextDiplomat/DebugExecutionAgent/DebugExecutionAgent.h"



void Nexus::Run(aFourthProof proof_)
{
	//SwapChainContextの代行クラス
	auto& swap_ExecutionAgent = swapChainContext->AccessDiplomat().Access<SwapChainContext::ExecutionAgent>();
	//CommandContextの代行クラス
	auto& cmd_Diplomat = commandContext->AccessDiplomat();
	auto& cmd_ExecutionAgent = cmd_Diplomat.Access<CommandContext::ExecutionAgent>();
	//SceneContextの代行クラス
	auto& scene_ExecutionAgent = sceneContext->AccessDiplomat().Access<SceneContext::ExecutionAgent>();
	//RenderContextの代行クラス
	auto& render_ExecutionAgent = renderContext->AccessDiplomat().Access<RenderContext::ExecutionAgent>();
	//DebugContextの代行クラス
	auto& debug_Diplomat = debugContext->AccessDiplomat();
	auto& debug_ExecutionAgent = debug_Diplomat.Access<DebugContext::ExecutionAgent>();

	//ImGuiのフレーム開始関数を呼ぶ
	debug_ExecutionAgent.BeginImGuiNewFrame(DebugContext::NexusFieldProof{});

	//シーンの更新処理
	scene_ExecutionAgent.RunScenePipeline(SceneContext::NexusFieldProof{});

	//フレームインデックスをスワップチェーンから取得
	auto const frameIndex = swap_ExecutionAgent.GetFrameIndex(SwapChainContext::NexusFieldProof{});

	//コマンドの記録開始
	cmd_ExecutionAgent.StartRecordingCommands(CommandContext::NexusFieldProof{}, frameIndex);

	//シーンデータのバッファへのバッチング
	scene_ExecutionAgent.BatchSceneData
	(
		SceneContext::NexusFieldProof{},
		frameIndex,
		modelContext->AccessDiplomat(),
		cameraContext->AccessDiplomat(),
		bufferContext->AccessDiplomat(),
		materialContext->AccessDiplomat()
	);

	//全ての描画コマンドはここに(ImGuiも)
	render_ExecutionAgent.RenderGraphRun
	(
		RenderContext::NexusFieldProof{},
		frameIndex,
		descriptorHeapContext->AccessDiplomat(),
		cmd_Diplomat,
		bufferContext->AccessDiplomat(),
		sceneContext->AccessDiplomat(),
		swapChainContext->AccessDiplomat(),
		debug_Diplomat
	);

	//コマンドを送る
	cmd_ExecutionAgent.ExecuteCommands(CommandContext::NexusFieldProof{},frameIndex);


	//表示
	swap_ExecutionAgent.Present(SwapChainContext::NexusFieldProof{});
}
