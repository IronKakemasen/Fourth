#include "PreCompileHeader.h"
#include "CommonCmdExecutor.h"


//外部
#include "../../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../../Buffer/GlobalConstantBuffers/GlobalConstantBuffers.h"

#include "../../../../../Core/DescriptorHeap/DescriptorHeapContextDiplomats.h"

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
	DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
	RuntimeWrapper& runtimeWrapper_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//srvDescriptorHeapにアクセス
	auto dToolLender = descriptorHeapContextDiplomat_.Access<DescriptorHeapContext::ToolLender>();
	DescriptorHeapContext::ToolLender::LicenceType<ID3D12DescriptorHeap> dLicence;
	auto* srvUavDescriptorHeap = dToolLender->Lend<ID3D12DescriptorHeap>(dLicence);

	//GlobalConstantBuffersにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::GlobalConstantBuffers> bLicence;
	auto& globalConstantBuffers = *bToolLender->Lend<BufferContext::GlobalConstantBuffers>(bLicence);


	//ルートシグネチャをセット
	SetGraphicsRootSignature(runtimeWrapper_);

	//srvuavディスクリプタヒープをセット
	SetDescriptorHeaps(srvUavDescriptorHeap, runtimeWrapper_);
	
	//フローバル定数バッファビューを転送
	SetGlobalConstantViews
	(
		frameIndex_,
		runtimeWrapper_,
		globalConstantBuffers.WatchGPUAddressContainer()
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
