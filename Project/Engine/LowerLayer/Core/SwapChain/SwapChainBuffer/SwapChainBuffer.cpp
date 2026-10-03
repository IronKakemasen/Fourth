#include "PreCompileHeader.h"
#include "SwapChainBuffer.h"


SwapChainContext::SwapChainBuffer::SwapChainBuffer
(
	NexusFieldProof proof_,
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> resources_,
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> const& rtvHandles_
)
{
	for (int i = 0;i < (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;++i)
	{
		buffers[i].resource = std::move(resources_.at(i));
		buffers[i].rtvHandle = rtvHandles_[i];
	}
}
