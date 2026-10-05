#include "PreCompileHeader.h"
#include "FinalRenderer.h"


//外部
#include "../../../../../Core/SwapChain/SwapChainContextDiplomats.h"
#include "../../../../../Core/SwapChain/SwapChainBuffer/SwapChainBuffer.h"

#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

#include "../../../../../../../Assets/Shared/ConstantBuffers.h"

#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"


RenderContext::StaticRenderGraph::FinalRenderer::FinalRenderer
(
	NexusFieldProof proof_,
	ID3D12PipelineState* finalRenderingPso_,
	BufferUniqueID finalRefBufferID_
)
	:finalRenderingPso(finalRenderingPso_), finalRefBufferID(finalRefBufferID_)
{

}



void RenderContext::StaticRenderGraph::FinalRenderer::Update
(
	UINT const frameIndex_,
	RuntimeWrapper& runtimeWrapper_,
	SwapChainContextDiplomat& swapChainContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//スワップチェーンバッファにアクセスする
	auto sToolLender = swapChainContextDiplomat_.Access<SwapChainContext::ToolLender>();
	SwapChainContext::ToolLender::LicenceType<SwapChainContext::SwapChainBuffer> sLicence;
	auto& swapChianBuffer = sToolLender.Lend<SwapChainContext::SwapChainBuffer>(sLicence);

	//BufferDispatcherにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> bLicence;
	auto& bufferDispatcher = *bToolLender->Lend<BufferContext::BufferDispatcher>(bLicence);

	auto const& rtvHandle = swapChianBuffer.OutProperRtvHandle(frameIndex_);
	auto const& viewport_scissor = swapChianBuffer.WatchMatrices();

	//参照するカラーバッファsrvIndexをルートコンスタンツで送る
	auto* refColorBuffer = static_cast<ColorBuffer*>(bufferDispatcher.Dispatch(finalRefBufferID));
	SRVHeapIndex refBufferSrvHeapIndex = refColorBuffer->OutProperSRVHeapIndex();
	auto const bindSlot = (UINT)ConstantBuffers::RootConstantsBindSlots::kFinalColorBufferSrv;

	runtimeWrapper_.SetGraphicsRoot32BitConstants
	(
		bindSlot,
		ConstantBuffers::Num32BitValuesTable(bindSlot),
		&refBufferSrvHeapIndex,
		0
	);


	//バリアを張る→renderTarget
	auto barrier = swapChianBuffer.CreateBarrier<D3D12_RESOURCE_STATE_RENDER_TARGET>(frameIndex_);
	runtimeWrapper_.ResourceBarrier(1, &barrier);

	//クリア
	runtimeWrapper_.ClearRenderTargetView(rtvHandle, swapChianBuffer.WatchClearColor(), 0, nullptr);

	//描画先に設定
	runtimeWrapper_.OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	//DXの行列の設定
	runtimeWrapper_.RSSetViewports(1, viewport_scissor.first);
	runtimeWrapper_.RSSetScissorRects(1, viewport_scissor.second);

	//psoのセット
	runtimeWrapper_.SetPipelineState(finalRenderingPso);

	//描画
	runtimeWrapper_.DispatchMesh(3, 1, 1);

	//バリアを張る→Present
	barrier = swapChianBuffer.CreateBarrier<D3D12_RESOURCE_STATE_PRESENT>(frameIndex_);
	runtimeWrapper_.ResourceBarrier(1, &barrier);
}
