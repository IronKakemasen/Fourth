#pragma once
#include "../SwapChainContext.h"

class SwapChainContext::SwapChainBuffer
{
public:

	SwapChainBuffer
	(
		NexusFieldProof proof_,
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> resources_,
		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> const& rtvHandles_
	);


	struct Buffer
	{
		Microsoft::WRL::ComPtr <ID3D12Resource> resource;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle{};
		//初期化ステートはこれ以外無いと思うので決め打ち
		D3D12_RESOURCE_STATES resourceState = D3D12_RESOURCE_STATE_PRESENT;

		D3D12_RESOURCE_BARRIER CreateBarrier(D3D12_RESOURCE_STATES after_);
	};

private:

	std::array<Buffer, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> buffers;

};

