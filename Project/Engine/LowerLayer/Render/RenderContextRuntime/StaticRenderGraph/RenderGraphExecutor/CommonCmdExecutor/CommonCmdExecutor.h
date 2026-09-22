#pragma once
#include "../../StaticRenderGraph.h"
#include "../../../../../Core/Command/CommandContext.h"

class RenderContext::StaticRenderGraph::CommonCmdExecutor
{
public:

	CommonCmdExecutor(NexusFieldProof proof_, ID3D12RootSignature* graphicsRootSig_);

	void Execute
	(
		UINT const frameIndex_,
		ID3D12DescriptorHeap* descriptorHeap_,
		CommandContext::RuntimeWrapper& runtimeWrapper_,
		std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> const& constantsGPU_
	);


	//以下ヘルパー
private:

	void SetGlobalConstantViews
	(
		UINT const frameIndex_, 
		CommandContext::RuntimeWrapper& runtimeWrapper_,
		std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> const& constantsGPU_
	);

	void SetGraphicsRootSignature
	(
		CommandContext::RuntimeWrapper& runtimeWrapper_
	);

	void SetDescriptorHeaps
	(
		ID3D12DescriptorHeap* descriptorHeap_,
		CommandContext::RuntimeWrapper& runtimeWrapper_
	);


	ID3D12RootSignature* graphicsRootSig;


};

