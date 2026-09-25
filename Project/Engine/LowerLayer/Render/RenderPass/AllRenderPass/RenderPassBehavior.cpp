#include "PreCompileHeader.h"
#include "RenderPassBehavior.h"
#include "../PassDesc/PassDesc.h"
#include "../RuntimePassInfo/RuntimePassInfo.h"


//外部
#include "../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"
#include "../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"



RenderContext::PassBehavior::PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_)
	:desc(std::move(desc_))
{
	
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderContext::PassDesc const* RenderContext::PassBehavior::WatchDesc() const
{
	return desc ? desc.get() : nullptr;
}

void RenderContext::PassBehavior::CreatePassInfo
(
	NexusFieldProof proof_,
	std::unordered_map<std::string, BufferUniqueID> const& idMap_,
	UINT const refOffset_
) 
{
	runtimePassInfo.reset(new RuntimePassInfo(proof_, std::move(desc), idMap_, refOffset_));
}

void RenderContext::PassBehavior::BeginPass(RuntimeWrapper& cmdWrapper_, BufferContext::BufferDispatcher& bufDispatcher_)
{
	auto const& colorBuffersInfo = runtimePassInfo->WatchColorBuffersInfo();
	UINT const numColorBuffers = (UINT)colorBuffersInfo.size();

	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> rtHandles;
	std::array<D3D12_RECT, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> scissorRects;
	std::array<D3D12_VIEWPORT, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> viewports;

	for (size_t i = 0;i < numColorBuffers;++i)
	{
		auto const& src = colorBuffersInfo[i];

		scissorRects[i] = src.scissorRect;
		viewports[i] = src.viewport;

		//IDからカラーバッファを検索
		auto* colorBuffer = static_cast<ColorBuffer*>(bufDispatcher_.Dispatch(src.bufferID));
		auto* iColorBuffer = static_cast<IColorBuffer*>(colorBuffer);
		
		//ダブルかシングル問わず、内部ステートに基づいて適切なハンドルを取得
		rtHandles[i] = iColorBuffer->OutProperRTVHeapHandle();

		//クリアカラーでクリア
		cmdWrapper_.ClearRenderTargetView(rtHandles[i], src.clearColor.data(), 0, nullptr);
	}

	//DXの行列の設定
	cmdWrapper_.RSSetScissorRects(numColorBuffers, scissorRects.data());
	cmdWrapper_.RSSetViewports(numColorBuffers, viewports.data());


	//深度ステンシルバッファも同様に
	auto const& depthSInfo = runtimePassInfo->WatchDepthStencilBufferInfo();

	if (depthSInfo.has_value())
	{
		//IDから深度ステンシルバッファを検索
		auto* depthSBuffer = static_cast<DepthStencilBuffer*>(bufDispatcher_.Dispatch(depthSInfo->bufferID));
		IDepthBuffer* iDepth = static_cast<IDepthBuffer*>(depthSBuffer);
		
		//ハンドルを入れる
		D3D12_CPU_DESCRIPTOR_HANDLE depthHandle = iDepth->OutProperDSVHeapHandle();
		//クリアする
		cmdWrapper_.ClearDepthStencilView(depthHandle, depthSInfo->doesClearStencil, depthSInfo->clearDepth, depthSInfo->clearStencil, 0, nullptr);
		//描画先としてセット
		cmdWrapper_.OMSetRenderTargets(numColorBuffers, rtHandles.data(), false, &depthHandle);
	}
	else
	{
		//深度ステンシルなし
		cmdWrapper_.OMSetRenderTargets(numColorBuffers, rtHandles.data(), false, nullptr);
	}
}


