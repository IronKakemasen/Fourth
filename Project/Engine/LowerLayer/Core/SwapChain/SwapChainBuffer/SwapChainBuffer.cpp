#include "PreCompileHeader.h"
#include "SwapChainBuffer.h"


D3D12_RESOURCE_BARRIER SwapChainContext::SwapChainBuffer::Buffer::CreateBarrier(D3D12_RESOURCE_STATES after_)
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Transition.pResource = resource.Get();
	barrier.Transition.StateBefore = resourceState;
	barrier.Transition.StateAfter = after_;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	resourceState = after_;
	return barrier;
}

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

	AssembleMatrices();
}


void SwapChainContext::SwapChainBuffer::AssembleMatrices()
{
	viewport.Width = static_cast<FLOAT>(ProjectConfig::Window::kWidth);
	viewport.Height = static_cast<FLOAT>(ProjectConfig::Window::kHeight);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	scissorRect.right = static_cast<LONG>(ProjectConfig::Window::kWidth);
	scissorRect.bottom = static_cast<LONG>(ProjectConfig::Window::kHeight);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);

}


D3D12_CPU_DESCRIPTOR_HANDLE const& SwapChainContext::SwapChainBuffer::OutProperRtvHandle(UINT const frameIndex_)const
{
	return buffers[frameIndex_].rtvHandle;
}

std::pair<D3D12_VIEWPORT const*, D3D12_RECT const*> SwapChainContext::SwapChainBuffer::WatchMatrices()const
{
	return std::make_pair(&viewport, &scissorRect);
}

template<>
D3D12_RESOURCE_BARRIER SwapChainContext::SwapChainBuffer::CreateBarrier<D3D12_RESOURCE_STATE_RENDER_TARGET>(UINT const frameIndex_)
{
	return buffers[frameIndex_].CreateBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET);
}

template<>
D3D12_RESOURCE_BARRIER SwapChainContext::SwapChainBuffer::CreateBarrier<D3D12_RESOURCE_STATE_PRESENT>(UINT const frameIndex_)
{
	return buffers[frameIndex_].CreateBarrier(D3D12_RESOURCE_STATE_PRESENT);
}



template
D3D12_RESOURCE_BARRIER SwapChainContext::SwapChainBuffer::CreateBarrier<D3D12_RESOURCE_STATE_RENDER_TARGET>(UINT const frameIndex_);
template
D3D12_RESOURCE_BARRIER SwapChainContext::SwapChainBuffer::CreateBarrier<D3D12_RESOURCE_STATE_PRESENT>(UINT const frameIndex_);

