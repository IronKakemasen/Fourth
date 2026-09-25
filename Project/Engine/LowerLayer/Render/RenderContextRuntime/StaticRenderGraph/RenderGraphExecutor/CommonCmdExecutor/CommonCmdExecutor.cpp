#include "PreCompileHeader.h"
#include "CommonCmdExecutor.h"


//外部
#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"
#include "../../../../../../../Assets/Shared/ConstantBuffers.h"

using namespace ProjectConfig::Render;
using namespace ConstantBuffers;

RenderContext::StaticRenderGraph::CommonCmdExecutor::CommonCmdExecutor(NexusFieldProof proof_, ID3D12RootSignature* graphicsRootSig_)
	:graphicsRootSig(graphicsRootSig_)
{

}


void RenderContext::StaticRenderGraph::CommonCmdExecutor::ExecuteCommonCmds
(
	UINT const frameIndex_,
	ID3D12DescriptorHeap* srvDescriptorHeap_,
	RuntimeWrapper& runtimeWrapper_,
	std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)NumBuffer::kDoubleBuffer> const& constantsGPU_
)
{
	//ルートシグネチャをセット
	SetGraphicsRootSignature(runtimeWrapper_);

	//srvuavディスクリプタヒープをセット
	SetDescriptorHeaps(srvDescriptorHeap_, runtimeWrapper_);
	
	//フローバル定数バッファビューを転送
	SetGlobalConstantViews
	(
		frameIndex_,
		runtimeWrapper_,
		constantsGPU_
	);
}


void RenderContext::StaticRenderGraph::CommonCmdExecutor::SetGraphicsRootSignature
(
	RuntimeWrapper& runtimeWrapper_
)
{
	runtimeWrapper_.SetGraphicsRootSignature(graphicsRootSig);
}

void RenderContext::StaticRenderGraph::CommonCmdExecutor::SetGlobalConstantViews
(
	UINT const frameIndex_,
	RuntimeWrapper& runtimeWrapper_,
	std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)NumBuffer::kDoubleBuffer> const& constantsGPU_
)
{
	for (UINT i = 0; i < (UINT)ConstantBufferBindSlots::kCount;++i)
	{
		runtimeWrapper_.SetGraphicsRootConstantBufferView(i,constantsGPU_[frameIndex_][i]);
	}
}


void RenderContext::StaticRenderGraph::CommonCmdExecutor::SetDescriptorHeaps
(
	ID3D12DescriptorHeap* descriptorHeap_,
	RuntimeWrapper& runtimeWrapper_
)
{
	ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap_ };
	runtimeWrapper_.SetDescriptorHeaps(1, descriptorHeaps);
}
