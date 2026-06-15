#include "PreCompileHedder.h"
#include "SwapChainColorBuffer.h"


SwapChainContext::ColorBuffer::ColorBuffer
(
	float clearColor_[4],
	DXGI_FORMAT format_
)
{
	for (int i = 0;i < 4;++i) desc.clearColor[i] = clearColor_[i];
	desc.format = format_;
}

void SwapChainContext::ColorBuffer::OverrideHeapIndex(SwapChainContext::InstanceKey instanceKey_,int index_ ,D3D12_CPU_DESCRIPTOR_HANDLE handle_)
{
	cpuHandles.at(index_) = handle_;
}

ID3D12Resource* SwapChainContext::ColorBuffer::GetResource(SwapChainContext::ResourceGetKey key_, int index_)
{
	return resources[index_].Get(); 
}



D3D12_RENDER_TARGET_VIEW_DESC SwapChainContext::ColorBuffer::CreateRTV_Desc()const
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	//出力結果をSRGBに変換する
	rtvDesc.Format = desc.format;
	//2Dテクスチャとして書き込む
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.PlaneSlice = 0;
	rtvDesc.Texture2D.MipSlice = 0;

	return rtvDesc;
}

DXGI_SWAP_CHAIN_DESC1 SwapChainContext::ColorBuffer::CreateSwapChainDesc()const
{
	using namespace ProjectConfig::Window;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//画面の縦横。クライアント領域と同じにしておく
	swapChainDesc.Width = (UINT)kWidth;
	swapChainDesc.Height = (UINT)kHeight;
	//色の形成
	swapChainDesc.Format = desc.format;
	//マルチサンプルしない
	swapChainDesc.SampleDesc.Count = 1;
	//描画のターゲットとして利用する
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//ダブルバッファ
	swapChainDesc.BufferCount = 2;
	//モニタに移したら中身を破棄
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	return swapChainDesc;
}


