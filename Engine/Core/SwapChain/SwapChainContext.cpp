#include "PreCompileHeader.h"
#include "SwapChainContext.h"
#include "SwapChainColorBuffer/SwapChainColorBuffer.h"
#include "../DescriptorHeap/ViewCreator/ViewCreator.h"

namespace
{
	std::string fileName = "SwapChainContext.cpp";
}

SwapChainContext::SwapChainContext
(
	InstanceKey instanceKey_,
	ViewCreator& viewCreator_,
	CommandCreateSwapChain cmdCreateSwapChain_,
	std::array<float, 4> clearColor_,
	DXGI_FORMAT format_,
	const HWND hWnd_,
	ID3D12CommandQueue* commandQueue_
)
{
	Logger::Entry("SwapChainContext: Constructor");

	//構築
	Assemble(instanceKey_, viewCreator_, cmdCreateSwapChain_, clearColor_, format_, hWnd_, commandQueue_);

	Logger::End("SwapChainContext: Constructor");

}

SwapChainContext::~SwapChainContext()
{

}

void SwapChainContext::CreateSwapChain
(
	CommandCreateSwapChain cmdCreateSwapChain_,
	const DXGI_SWAP_CHAIN_DESC1& desc_, 
	const HWND hWnd_,
	ID3D12CommandQueue* commandQueue_
)
{
	HRESULT hr = cmdCreateSwapChain_(commandQueue_, desc_, swapChain.GetAddressOf(), hWnd_);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "SwapChain生成失敗", fileName);
}

void SwapChainContext::Assemble
(
	InstanceKey instanceKey_,
	ViewCreator& viewCreator_,
	CommandCreateSwapChain cmdCreateSwapChain_,
	std::array<float, 4> clearColor_,
	DXGI_FORMAT format_,
	const HWND hWnd_,
	ID3D12CommandQueue* commandQueue_
)
{
	using namespace ProjectConfig::Render;


	//ディスクリプション
	std::unique_ptr<SwapChainContext::ColorBuffer::Description> desc =
		std::make_unique<SwapChainContext::ColorBuffer::Description>(clearColor_, format_);

	//生リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>,kRequiredGPUBufferSum > resources;

	//rtvDesc
	auto rtvDesc = desc->CreateRTV_Desc();

	//スワップチェーン、生リソース生成
	{
		auto swapChainDesc = desc->CreateSwapChainDesc();

		CreateSwapChain(cmdCreateSwapChain_,swapChainDesc, hWnd_, commandQueue_);
		Logger::Log("Create: SwapChain", fileName);

		//スワップチェーンからリソースを引っ張る
		HRESULT hr{};
		for (int i = 0;i < kRequiredGPUBufferSum;++i)
		{
			hr = swapChain->GetBuffer(i, IID_PPV_ARGS(resources.at(i).GetAddressOf()));
			ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "SwapChainのリソースを引っ張れなかった", fileName);
		}

		Logger::Log("Complete: Pull SwapChainResources", fileName);
	}

	//バッファ生成
	colorBuffer.reset(new SwapChainContext::ColorBuffer(std::move(desc), std::move(resources)));

	//ビュー生成
	{
		ResourceGetKey resourceGetKey;

		for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

			//Rtvを作成
			std::tie(std::ignore, rtvCPU, std::ignore) =
				viewCreator_.CreateView(colorBuffer->GetResource(resourceGetKey, i), rtvDesc);

			//インデックスを書き込む
			colorBuffer->OverrideHeapIndex(i, rtvCPU);
		}

		Logger::Log("Create: SwapChainResourceRTV", fileName);
	}

}
