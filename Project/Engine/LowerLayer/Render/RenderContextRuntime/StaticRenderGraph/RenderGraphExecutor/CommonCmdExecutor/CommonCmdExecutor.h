#pragma once
#include "../../StaticRenderGraph.h"
#include "../../../../../Core/Command/CommandContext.h"

class RenderContext::StaticRenderGraph::CommonCmdExecutor
{
public:

	CommonCmdExecutor(NexusFieldProof proof_, ID3D12RootSignature* graphicsRootSig_);

	void ExecuteCommonCmds
	(
		UINT const frameIndex_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
		RuntimeWrapper& runtimeWrapper_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	//以下ヘルパー
private:

	void SetGlobalConstantViews
	(
		UINT const frameIndex_, 
		RuntimeWrapper& runtimeWrapper_,
		std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> const& constantsGPU_
	);

	void SetGraphicsRootSignature
	(
		RuntimeWrapper& runtimeWrapper_
	);

	void SetDescriptorHeaps
	(
		ID3D12DescriptorHeap* descriptorHeap_,
		RuntimeWrapper& runtimeWrapper_
	);


	ID3D12RootSignature* graphicsRootSig;
};

