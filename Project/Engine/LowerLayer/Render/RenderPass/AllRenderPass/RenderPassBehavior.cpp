#include "PreCompileHeader.h"
#include "RenderPassBehavior.h"
#include "../PassDesc/PassDesc.h"
#include "../RuntimePassInfo/RuntimePassInfo.h"
#include "../../RenderContextRuntime/PSO_PoolDispatcher/PSO_PoolDispatcher.h"


//外部
#include "../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"
#include "../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

#include "../../../Resource/Model/ModelStructure/Model.h"



RenderContext::PassBehavior::PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_)
	:desc(std::move(desc_))
{
	
}

using namespace RenderStateComponent;

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderContext::PassDesc const* RenderContext::PassBehavior::WatchDesc() const
{
	return desc ? desc.get() : nullptr;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::CreatePassInfo
(
	NexusFieldProof proof_,
	std::unordered_map<std::string, BufferUniqueID> const& idMap_,
	UINT const refOffset_
) 
{
	runtimePassInfo.reset(new RuntimePassInfo(proof_, std::move(desc), idMap_, refOffset_));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::BeginPass(RuntimeWrapper& cmdWrapper_, BufferContext::BufferDispatcher& bufDispatcher_)
{
	auto const& colorBuffersInfo = runtimePassInfo->WatchColorBuffersInfo();
	UINT const numColorBuffers = UINT(colorBuffersInfo.size());
	auto const& DepthStencilBufferInfo = runtimePassInfo->WatchDepthStencilBufferInfo();

	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> rtHandles;
	std::array<D3D12_RECT, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> scissorRects;
	std::array<D3D12_VIEWPORT, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> viewports;


	//カラーバッファ
	for (UINT i = 0;i < numColorBuffers;++i)
	{
		auto const& src = colorBuffersInfo[i];

		//バッファ検索
		ColorBuffer* colorBuffer = FindBufferWithID<ColorBuffer>(src.bufferID, bufDispatcher_);
		
		//パラメーターかき集め
		rtHandles[i] = PullHandleCPU<ColorBuffer>(colorBuffer, bufDispatcher_);
		scissorRects[i] = src.scissorRect;
		viewports[i] = src.viewport;

		//ビュークリア
		ClearColorBufferView(rtHandles[i], src.clearColor.data(), cmdWrapper_);
	}

	//深度ステンシルバッファ
	if (DepthStencilBufferInfo.has_value())
	{
		//バッファ検索
		auto* depthStencilBuffer = FindBufferWithID<DepthStencilBuffer>(DepthStencilBufferInfo->bufferID, bufDispatcher_);

		//ハンドル取得
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = PullHandleCPU<DepthStencilBuffer>(depthStencilBuffer, bufDispatcher_);
		
		//ビュークリア
		ClearDepthStencilBufferView(dsvHandle, cmdWrapper_);

		//描画先の設定
		SetRenderTargets(rtHandles, numColorBuffers, &dsvHandle, cmdWrapper_);
	}
	//無ければ
	else
	{
		//描画先の設定
		SetRenderTargets(rtHandles, numColorBuffers, nullptr, cmdWrapper_);
	}

	//このパスのルートコンスタンツを転送
	TransferRootConstants(cmdWrapper_);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::DrawModels
(
	std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
	RenderStateComponent::FillMode const fillMode_,
	PSO_PoolDispatcher& psoDispatcher_,
	RuntimeWrapper& cmdWrapper_
)
{
	//PSOキー
	GraphicsPSO_Key psoKey;
	psoKey.pass = runtimePassInfo->WatchPass();
	psoKey.fill = fillMode_;

	//このPassで描画対象の全モデルの走査
	for (auto const& [key, state_models] : modelContainer_)
	{
		//レンダーステートキーからPSOキーの一部を入力
		WritePsoKeyFromRenderStateKey(state_models.first, psoKey);
		
		//psoDispatcherがキーをもとにpsoを検索
		auto* srcPso = psoDispatcher_.AccessGraphicsPSO(psoKey);
		
		//psoをセット
		cmdWrapper_.SetPipelineState(srcPso);

		//おなじPSOごとに仕分けられているので、そこでも走査
		for (auto const& model : state_models.second)
		{
			//そのモデルを描画するかどうか
			if (!model->DoesDraw(psoKey.blend, psoKey.material)) continue;

			//以下マルチメッシュ分も含めてドローコール
			auto const& perDrawIndices = model->WatchPerDrawIndices();
			auto const& meshletSize = model->WatchMeshletSize();

			for (size_t i = 0;i < meshletSize.size();++i)
			{
				//モデルのルートコンスタンツを転送
				cmdWrapper_.SetGraphicsRoot32BitConstants
				(
					(UINT)ConstantBuffers::RootConstantsBindSlots::kPerDrawIndices,
					3,
					&perDrawIndices[i],
					0
				);

				//ドロー
				cmdWrapper_.DispatchMesh((UINT)meshletSize[i], 1, 1);
			}
		}
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::TransferRootConstants(RuntimeWrapper& cmdWrapper_)
{
	cmdWrapper_.SetGraphicsRoot32BitConstants
	(
		(UINT)ConstantBuffers::RootConstantsBindSlots::kPassBufferIndexRange,
		2,                    
		&runtimePassInfo->WatchRootConstants(),
		0
	);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::SetRenderTargets
(
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> const& rtHandles_,
	UINT const numRT_,
	D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle_,
	RuntimeWrapper& cmdWrapper_
)
{
	cmdWrapper_.OMSetRenderTargets(numRT_, rtHandles_.data(), false, depthHandle_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::PassBehavior::PullHandleCPU
(
	ColorBuffer* buffer_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{
	auto* iColorBuffer = static_cast<IColorBuffer*>(buffer_);

	return iColorBuffer->OutProperRTVHeapHandle();
}
template<>
D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::PassBehavior::PullHandleCPU
(
	DepthStencilBuffer* buffer_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{
	IDepthBuffer* iDepth = static_cast<IDepthBuffer*>(buffer_);

	return iDepth->OutProperDSVHeapHandle();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
ColorBuffer* RenderContext::PassBehavior::FindBufferWithID
(
	BufferUniqueID const id_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{
	//IDからカラーバッファを検索
	return static_cast<ColorBuffer*>(bufDispatcher_.Dispatch(id_));
}

template<>
DepthStencilBuffer* RenderContext::PassBehavior::FindBufferWithID
(
	BufferUniqueID const id_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{
	//IDから深度ステンシルバッファを検索
	return static_cast<DepthStencilBuffer*>(bufDispatcher_.Dispatch(id_));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::ClearColorBufferView
(
	D3D12_CPU_DESCRIPTOR_HANDLE const handleCPU_,
	const FLOAT* clearColorPtr_,
	RuntimeWrapper& cmdWrapper_
)
{
	cmdWrapper_.ClearRenderTargetView(handleCPU_, clearColorPtr_, 0, nullptr);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PassBehavior::ClearDepthStencilBufferView
(
	D3D12_CPU_DESCRIPTOR_HANDLE const handleCPU_,
	RuntimeWrapper& cmdWrapper_
)
{
	auto const& depthSInfo = runtimePassInfo->WatchDepthStencilBufferInfo();

	cmdWrapper_.ClearDepthStencilView(handleCPU_, depthSInfo->doesClearStencil, depthSInfo->clearDepth, depthSInfo->clearStencil, 0, nullptr);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void RenderContext::PassBehavior::SetMatrix<D3D12_VIEWPORT>
(
	UINT const num_,
	const D3D12_VIEWPORT* matrix_,
	RuntimeWrapper& cmdWrapper_
)
{
	cmdWrapper_.RSSetViewports(num_, matrix_);
}

template<>
void RenderContext::PassBehavior::SetMatrix<D3D12_RECT>
(
	UINT const num_,
	const D3D12_RECT* matrix_,
	RuntimeWrapper& cmdWrapper_
)
{
	cmdWrapper_.RSSetScissorRects(num_, matrix_);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
D3D12_RESOURCE_BARRIER RenderContext::PassBehavior::CreateBarrier<BufferUsage::kRead>(IRenderTargetBuffer* buffer_)
{
	return buffer_->CreateBarrier(BufferUsage::kRead);
}

template<>
D3D12_RESOURCE_BARRIER RenderContext::PassBehavior::CreateBarrier<BufferUsage::kWrite>(IRenderTargetBuffer* buffer_)
{
	return buffer_->CreateBarrier(BufferUsage::kWrite);
}

template
D3D12_RESOURCE_BARRIER RenderContext::PassBehavior::CreateBarrier<BufferUsage::kRead>(IRenderTargetBuffer* buffer_);
template
D3D12_RESOURCE_BARRIER RenderContext::PassBehavior::CreateBarrier<BufferUsage::kWrite>(IRenderTargetBuffer* buffer_);
