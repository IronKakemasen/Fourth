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
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 
		ProjectConfig::Render::kRequiredGPUBufferSum> resources_
	);

	//リソース取得
	inline ID3D12Resource* GetResource(SwapChainContext::ResourceGetKey key_, int index_) { return buffers.at(index_).resource.Get(); }
	//ヒープインデックスの上書き
	void OverrideHeapIndex(SwapChainContext::InstanceKey instanceKey_, int index_, D3D12_CPU_DESCRIPTOR_HANDLE handle_);

	//MaterialProviderが情報を欲する
	friend class SwapChainContext::RenderPassMaterialProvider;

private:

	void AssembleMatrix();

	struct Buffer
	{
		Microsoft::WRL::ComPtr <ID3D12Resource> resource;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
		D3D12_RESOURCE_STATES state;
	};

	std::array<Buffer, ProjectConfig::Render::kRequiredGPUBufferSum> buffers;

	//std::array<Microsoft::WRL::ComPtr<ID3D12Resource>,ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	//std::array<D3D12_CPU_DESCRIPTOR_HANDLE, ProjectConfig::Render::kRequiredGPUBufferSum> cpuHandles;

	std::unique_ptr<SwapChainContext::Description> desc;

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;
	D3D12_RESOURCE_STATES resourceState;
};

