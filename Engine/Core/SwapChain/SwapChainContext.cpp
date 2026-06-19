#include "PreCompileHeader.h"
#include "SwapChainContext.h"
#include "SwapChainColorBuffer/SwapChainColorBuffer.h"
#include "../DescriptorHeap/ViewCreator/ViewCreator.h"
#include "../Command/CommandContext.h"
#include "Presenter/Presenter.h"
#include "RenderPassMaterialProvider/RenderPassMaterialProvider.h"
#include "../../Resource/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"


namespace
{
	std::string fileName = "SwapChainContext.cpp";
}

SwapChainContext::SwapChainContext
(
	InstanceKey instanceKey_,
	DescriptorHeapContext* descriptorHeapContext_,
	CommandContext* commandContext_,
	CommandCreateSwapChain cmdCreateSwapChain_,
	const HWND hWnd_,
	std::unique_ptr<DepthStencilBuffer> depthStencilBuffer_
)
{
	Logger::Entry("SwapChainContext: Constructor");

	{
		//コマンドキューを一時的に借りる
		auto* commandQueue = commandContext_->GetCommandQueue(CommandContext::CmdQueueGetKey{});
		//ビュークリエイターも一時的に借りる
		auto& viewCreator = *descriptorHeapContext_->GetViewCreator(DescriptorHeapContext::ViewCreatorGetKey{});
		//構築
		Assemble(instanceKey_, viewCreator, cmdCreateSwapChain_, hWnd_, commandQueue);
		Logger::Log("Assemble: core parts", fileName);
	}
	
	{
		presenter.reset(new Presenter(swapChain.Get()));
		Logger::Log("Instantiate: Presenter", fileName);
	}

	{
		renderPassMaterialProvider.reset(new RenderPassMaterialProvider(colorBuffer.get(), depthStencilBuffer.get()));
		Logger::Log("Instantiate: RenderPassMaterialProvider", fileName);
	}


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

void SwapChainContext::PullResourcesFromSwapChain(std::unique_ptr<Description>&& desc_)
{
	using namespace ProjectConfig::Render;

	//生リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kRequiredGPUBufferSum > resources;


	//スワップチェーンからリソースを引っ張る
	HRESULT hr{};
	for (int i = 0;i < kRequiredGPUBufferSum;++i)
	{
		hr = swapChain->GetBuffer(i, IID_PPV_ARGS(resources.at(i).GetAddressOf()));
		ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "SwapChainのリソースを引っ張れなかった", fileName);
	}

	//バッファ生成
	colorBuffer.reset(new SwapChainContext::ColorBuffer(std::move(desc_), std::move(resources)));

	Logger::Log("Complete: Pull SwapChainResources", fileName);
}

void SwapChainContext::CreateRTV(InstanceKey instanceKey_ , const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc_, ViewCreator& viewCreator_)
{
	ResourceGetKey resourceGetKey;

	for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

		//Rtvを作成
		std::tie(std::ignore, rtvCPU, std::ignore) =
			viewCreator_.CreateView(colorBuffer->GetResource(resourceGetKey, i), &rtvDesc_);

		//インデックスを書き込む
		colorBuffer->OverrideHeapIndex(instanceKey_,i, rtvCPU);
	}

}

void SwapChainContext::Assemble
(
	InstanceKey instanceKey_,
	ViewCreator& viewCreator_,
	CommandCreateSwapChain cmdCreateSwapChain_,
	const HWND hWnd_,
	ID3D12CommandQueue* commandQueue_
)
{
	using namespace ProjectConfig::Window;

	//ディスクリプション
	std::unique_ptr<Description> bufferDesc = std::make_unique<Description>(kColor, kRtFormat);

	//rtvDesc
	auto rtvDesc = bufferDesc->CreateRTV_Desc();
	//swapChainDesc
	auto swapChainDesc = bufferDesc->CreateSwapChainDesc();

	//スワップチェーン生成
	CreateSwapChain(cmdCreateSwapChain_, swapChainDesc, hWnd_, commandQueue_);
	Logger::Log("Create: SwapChain", fileName);

	//スワップチェーンからリソースを引っ張る
	PullResourcesFromSwapChain(std::move(bufferDesc));

	//ビュー生成
	CreateRTV(instanceKey_,rtvDesc, viewCreator_);
	Logger::Log("Create: SwapChainResourceRTV", fileName);
}
