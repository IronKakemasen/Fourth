#include "SwapChainContext.h"
#include "SwapChainColorBuffer/SwapChainColorBuffer.h"
#include "Presenter/Presenter.h"
#include "RenderPassMaterialProvider/RenderPassMaterialProvider.h"

#include "../Command/CommandContext.h"
#include "../DescriptorHeap/ViewCreator/ViewCreator.h"

using namespace ProjectConfig::Render;

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
	const HWND hWnd_
)
{
	Logger::Entry("SwapChainContext: Constructor");


	AssembleCoreParts(instanceKey_, descriptorHeapContext_, commandContext_, cmdCreateSwapChain_, hWnd_);
	Logger::Log("Assemble: core parts", fileName);

	presenter.reset(new Presenter(swapChain.Get()));
	Logger::Log("Instantiate: Presenter", fileName);

	renderPassMaterialProvider.reset(new RenderPassMaterialProvider(colorBuffer.get()));
	Logger::Log("Instantiate: RenderPassMaterialProvider", fileName);


	Logger::End("SwapChainContext: Constructor");
}

SwapChainContext::~SwapChainContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwapChainContext::CreateSwapChain
(
	CommandCreateSwapChain cmdCreateSwapChain_,
	const DXGI_SWAP_CHAIN_DESC1& desc_,
	const HWND hWnd_,
	ID3D12CommandQueue* commandQueue_
)
{

	cmdCreateSwapChain_(commandQueue_, desc_, swapChain.GetAddressOf(), hWnd_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwapChainContext::AssembleCoreParts
(
	InstanceKey instanceKey_,
	DescriptorHeapContext* descriptorHeapContext_,
	CommandContext* commandContext_,
	CommandCreateSwapChain cmdCreateSwapChain_,
	const HWND hWnd_
)
{
	using namespace ProjectConfig::Window;

	//コマンドキューを一時的に借りる
	auto* commandQueue = commandContext_->GetCommandQueue(CommandContext::CmdQueueGetKey{});
	//ビュークリエイターも一時的に借りる
	auto& viewCreator = *descriptorHeapContext_->GetViewCreator(DescriptorHeapContext::ViewCreatorGetKey{});

	//ディスクリプション
	std::unique_ptr<Description> bufferDesc = std::make_unique<Description>(kColor, kRtFormat);

	//rtvDesc
	auto rtvDesc = bufferDesc->CreateRTV_Desc();
	//swapChainDesc
	auto swapChainDesc = bufferDesc->CreateSwapChainDesc();

	//スワップチェーン生成
	CreateSwapChain(cmdCreateSwapChain_, swapChainDesc, hWnd_, commandQueue);

	//スワップチェーンからリソースを引っ張る
	PullResourcesFromSwapChain(std::move(bufferDesc));

	//ビュー生成
	CreateRTV(instanceKey_, rtvDesc, viewCreator);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwapChainContext::PullResourcesFromSwapChain(std::unique_ptr<Description>&& desc_)
{

	//生リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)NumBuffer::kDoubleBuffer > resources;

	//スワップチェーンからリソースを引っ張る
	HRESULT hr{};
	for (int i = 0;i < (int)NumBuffer::kDoubleBuffer;++i)
	{
		hr = swapChain->GetBuffer(i, IID_PPV_ARGS(resources.at(i).GetAddressOf()));
		ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "SwapChainのリソースを引っ張れなかった", fileName);
	}

	//バッファ生成
	colorBuffer.reset(new SwapChainContext::ColorBuffer(std::move(desc_), std::move(resources)));

	Logger::Log("Complete: Pull SwapChainResources", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwapChainContext::CreateRTV(InstanceKey instanceKey_ , const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc_, DescriptorHeapContext::ViewCreator& viewCreator_)
{
	ResourceGetKey resourceGetKey;

	for (int i = 0;i < (int)NumBuffer::kDoubleBuffer;++i)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

		//Rtvを作成
		std::tie(std::ignore, rtvCPU, std::ignore) =
			viewCreator_.CreateView(colorBuffer->GetResource(resourceGetKey, i), &rtvDesc_);

		//インデックスを書き込む
		colorBuffer->OverrideHeapIndex(instanceKey_,i, rtvCPU);
	}

	Logger::Log("Create: SwapChainResourceRTV", fileName);
}

