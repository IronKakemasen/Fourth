#include "StaticRenderGraph.h"
#include "RenderGraphExecutor/CommonCmdExecutor/CommonCmdExecutor.h"
#include "RenderGraphExecutor/PathOperator/PathOperator.h"
#include "RenderGraphExecutor/FinalRenderer/FinalRenderer.h"

//外部
#include "../../../../LowerLayer/Core/Command/CommandContextDiplomats.h"



void RenderContext::StaticRenderGraph::Run
(
	NexusFieldProof proof_,
	AgentKey key_,
	UINT const frameIndex_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
	CommandContextDiplomat& commandContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	SceneContextDiplomat& sceneContextDiplomat_,
	SwapChainContextDiplomat& swapChainContextDiplomat_
)
{
	//runtimeCmdWrapperにアクセス
	auto& cToolLender = commandContextDiplomat_.Access<CommandContext::ToolLender>();
	CommandContext::ToolLender::LicenceType<RuntimeWrapper> cLicence;
	auto& runtimeCmdWrapper = *cToolLender.Lend<RuntimeWrapper>(cLicence);

	//共通の描画コマンドをたたく
	commonCmdExecutor->ExecuteCommonCmds
	(
		frameIndex_,
		descriptorHeapContextDiplomat_,
		runtimeCmdWrapper,
		bufferContextDiplomat_
	);

	//全Pathの更新処理
	pathOperator->Run
	(
		frameIndex_, 
		sceneContextDiplomat_,
		bufferContextDiplomat_,
		runtimeCmdWrapper
	);

	//最終描画
	finalRenderer->Update(frameIndex_, runtimeCmdWrapper, swapChainContextDiplomat_,bufferContextDiplomat_);

}

