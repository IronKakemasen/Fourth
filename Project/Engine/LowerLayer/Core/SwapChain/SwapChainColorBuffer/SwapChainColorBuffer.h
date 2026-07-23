#pragma once
#include "../SwapChainContext.h"


struct SwapChainContext::Description
{

	Description(std::array<float, 4> clearColor_, DXGI_FORMAT format_);

	D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const;
	DXGI_SWAP_CHAIN_DESC1 CreateSwapChainDesc()const;

	std::array<float, 4> clearColor = { 9,9,9,9 };
	DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;
};


//オンリーなバッファなので、抽象クラスを使わない
class SwapChainContext::ColorBuffer
{
public:

	ColorBuffer
	(
		std::unique_ptr<SwapChainContext::Description> desc_,
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> resources_
	);

	//リソース取得
	inline ID3D12Resource* GetResource(SwapChainContext::ResourceGetKey key_, int index_) { return buffers.at(index_).resource.Get(); }
	//ヒープインデックスの上書き
	void OverrideHeapIndex(SwapChainContext::NexusFieldProof proof_, int index_, D3D12_CPU_DESCRIPTOR_HANDLE handle_);
	//MaterialProviderが情報を欲する
	friend class SwapChainContext::RenderPassMaterialProvider;

private:

	void AssembleMatrix();

	struct Buffer
	{
		Microsoft::WRL::ComPtr <ID3D12Resource> resource;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
		//初期化ステートはこれ以外無いと思うので決め打ち
		D3D12_RESOURCE_STATES resourceState = D3D12_RESOURCE_STATE_COMMON;

		D3D12_RESOURCE_BARRIER CreateBarrier(D3D12_RESOURCE_STATES after_);
	};

	std::array<Buffer, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> buffers;
	std::unique_ptr<SwapChainContext::Description> desc;

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;
};

