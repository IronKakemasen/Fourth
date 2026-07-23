
#include "SwapChainColorBuffer.h"
#include "../../../Resource/Buffer/BufferDefinition/ResourceBarrier.h"


SwapChainContext::ColorBuffer::ColorBuffer
(
	std::unique_ptr<Description> desc_,
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> resources_
) : desc(std::move(desc_))
{
	//行列2種を構築
	AssembleMatrix();

	for (int i = 0;i < (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;++i)
	{
		buffers.at(i).resource = std::move(resources_.at(i));
	}

	Logger::Log("Assemble: Matrix", "SwapChainColorBuffer.cpp");
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwapChainContext::ColorBuffer::AssembleMatrix()
{
	using namespace ProjectConfig::Window;

	//クライアント領域と一緒のサイズにして画面全体に表示
	viewport.Width = static_cast<FLOAT>(kWidth);
	viewport.Height = static_cast<FLOAT>(kHeight);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//しざー矩形
	scissorRect.right = static_cast<LONG>(kWidth);
	scissorRect.bottom = static_cast<LONG>(kHeight);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);
}

void SwapChainContext::ColorBuffer::OverrideHeapIndex(SwapChainContext::NexusFieldProof proof_, int index_ ,D3D12_CPU_DESCRIPTOR_HANDLE handle_)
{
	buffers.at(index_).cpuHandle = handle_;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SwapChainContext::Description::Description(std::array<float, 4> clearColor_, DXGI_FORMAT format_)
{
	clearColor = clearColor_;
	format = format_;
}

D3D12_RENDER_TARGET_VIEW_DESC SwapChainContext::Description::CreateRTV_Desc()const
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

DXGI_SWAP_CHAIN_DESC1 SwapChainContext::Description::CreateSwapChainDesc()const
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
	swapChainDesc.BufferCount = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;
	//モニタに移したら中身を破棄
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	return swapChainDesc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_BARRIER SwapChainContext::ColorBuffer::Buffer::CreateBarrier(D3D12_RESOURCE_STATES after_)
{
	auto buff = resourceState;
	resourceState = after_;

	return ResourceBarrier::Create
	(
		resource.Get(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		buff,
		after_,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
	);
}