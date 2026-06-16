#pragma once
#include "../SwapChainContext.h"

//オンリーなバッファなので、抽象クラスを使わない
class SwapChainContext::ColorBuffer
{
public:

	struct Description
	{
		std::array<float,4> clearColor = { 9,9,9,9 };

		DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;

		Description(std::array<float, 4> clearColor_, DXGI_FORMAT format_);

		D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const;
		DXGI_SWAP_CHAIN_DESC1 CreateSwapChainDesc()const;
	};

	ColorBuffer
	(
		std::unique_ptr<Description> desc_,
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources_
	);

	//リソース取得
	inline ID3D12Resource* GetResource(SwapChainContext::ResourceGetKey key_, int index_) { return resources[index_].Get(); }
	//ヒープインデックスの上書き
	void OverrideHeapIndex(int index_, D3D12_CPU_DESCRIPTOR_HANDLE handle_);

private:

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>,ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, ProjectConfig::Render::kRequiredGPUBufferSum> cpuHandles;
	std::unique_ptr<Description> desc;

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

};

