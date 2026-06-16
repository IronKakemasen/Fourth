#include "PreCompileHeader.h"
#include "SwapChainColorBuffer.h"


SwapChainContext::ColorBuffer::ColorBuffer
(
	std::unique_ptr<Description> desc_,
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources_
) : desc(std::move(desc_)),resources(std::move(resources_))
{
	
}

SwapChainContext::ColorBuffer::Description::Description(std::array<float, 4> clearColor_, DXGI_FORMAT format_)
{
	clearColor = clearColor_;
	format = format_;
}


void SwapChainContext::ColorBuffer::OverrideHeapIndex(int index_ ,D3D12_CPU_DESCRIPTOR_HANDLE handle_)
{
	cpuHandles.at(index_) = handle_;
}


D3D12_RENDER_TARGET_VIEW_DESC SwapChainContext::ColorBuffer::Description::CreateRTV_Desc()const
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	//出力結果をSRGBに変換する
	rtvDesc.Format = format;
	//2Dテクスチャとして書き込む
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.PlaneSlice = 0;
	rtvDesc.Texture2D.MipSlice = 0;

	return rtvDesc;
}

DXGI_SWAP_CHAIN_DESC1 SwapChainContext::ColorBuffer::Description::CreateSwapChainDesc()const
{
	using namespace ProjectConfig::Window;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//画面の縦横。クライアント領域と同じにしておく
	swapChainDesc.Width = (UINT)kWidth;
	swapChainDesc.Height = (UINT)kHeight;
	//色の形成
	swapChainDesc.Format = format;
	//マルチサンプルしない
	swapChainDesc.SampleDesc.Count = 1;
	//描画のターゲットとして利用する
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//ダブルバッファ
	swapChainDesc.BufferCount = ProjectConfig::Render::kRequiredGPUBufferSum;
	//モニタに移したら中身を破棄
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	return swapChainDesc;
}


