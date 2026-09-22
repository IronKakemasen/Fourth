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


void RenderContext::StaticRenderGraph::CommonCmdExecutor::Execute
(
	UINT const frameIndex_,
	ID3D12DescriptorHeap* descriptorHeap_,
	CommandContext::RuntimeWrapper& runtimeWrapper_,
	std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)NumBuffer::kDoubleBuffer> const& constantsGPU_
)
{
	SetGraphicsRootSignature(runtimeWrapper_);

	SetDescriptorHeaps(descriptorHeap_, runtimeWrapper_);
	
	SetGlobalConstantViews
	(
		frameIndex_,
		runtimeWrapper_,
		constantsGPU_
	);
}


void RenderContext::StaticRenderGraph::CommonCmdExecutor::SetGraphicsRootSignature
(
	CommandContext::RuntimeWrapper& runtimeWrapper_
)
{
	runtimeWrapper_.SetGraphicsRootSignature(graphicsRootSig);
}

void RenderContext::StaticRenderGraph::CommonCmdExecutor::SetGlobalConstantViews
(
	UINT const frameIndex_,
	CommandContext::RuntimeWrapper& runtimeWrapper_,
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
	CommandContext::RuntimeWrapper& runtimeWrapper_
)
{
	ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap_ };
	runtimeWrapper_.SetDescriptorHeaps(1, descriptorHeaps);
}
