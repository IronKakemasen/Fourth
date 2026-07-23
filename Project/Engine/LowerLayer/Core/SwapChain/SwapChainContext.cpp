#include "SwapChainContext.h"
#include "SwapChainColorBuffer/SwapChainColorBuffer.h"
#include "Presenter/Presenter.h"
#include "RenderPassMaterialProvider/RenderPassMaterialProvider.h"


//外部
#include "../Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../Command/CommandContextDiplomat/CommandContextToolLender/CommandContextToolLender.h"
#include "../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"
#include "../DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"
#include "../DescriptorHeap/ViewCreator/ViewCreator.h"

using namespace ProjectConfig::Render;
using namespace ProjectConfig::Window;

namespace
{
	std::string fileName = "SwapChainContext.cpp";
}

SwapChainContext::SwapChainContext
(
	NexusFieldProof proof_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	CommandContextDiplomat* commandContextDiplomat_,
	DeviceContextDiplomat* deviceContextDiplomat_,
	const HWND hWnd_
)
{
	Logger::Entry("SwapChainContext: Constructor");

	//コアパーツを組み立てる
	AssembleCoreParts(proof_, descriptorheapContextDiplomat_, commandContextDiplomat_, deviceContextDiplomat_, hWnd_);
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
	NexusFieldProof proof_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	CommandContextDiplomat* commandContextDiplomat_,
	DeviceContextDiplomat* deviceContextDiplomat_,
	const HWND hWnd_
)
{

	//コマンドキューを一時的に借りる
	auto* commandContextToolLender = commandContextDiplomat_->Access<CommandContext::ToolLender>();
	CommandContext::ToolLender::LicenceType<ID3D12CommandQueue> cmdQueueAccesslicence{};
	auto* commandQueue = commandContextToolLender->Lend<ID3D12CommandQueue>(cmdQueueAccesslicence);
	
	//ディスクリプション
	std::unique_ptr<Description> bufferDesc = std::make_unique<Description>(kColor, kRtFormat);

	//rtvDesc
	auto rtvDesc = bufferDesc->CreateRTV_Desc();
	//swapChainDesc
	auto swapChainDesc = bufferDesc->CreateSwapChainDesc();

	//スワップチェーン生成
	auto commandProvider = deviceContextDiplomat_->Access<DeviceContext::CommandProvider>();
	auto createSwapChainCmd = commandProvider->ProvideCreateSwapChainCommand();
	CreateSwapChain(createSwapChainCmd, swapChainDesc, hWnd_, commandQueue);

	//スワップチェーンからリソースを引っ張る
	PullResourcesFromSwapChain(std::move(bufferDesc));

	//ビュー生成
	CreateRTV(proof_, rtvDesc, descriptorheapContextDiplomat_);
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
void SwapChainContext::CreateRTV
(
	NexusFieldProof proof_,
	const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_
)
{

	//ビュークリエイターを一時的に借りる
	DescriptorHeapContext::ToolLender::LicenceType<DescriptorHeapContext::ViewCreator> licence;
	auto* toolLender = descriptorheapContextDiplomat_->Access<DescriptorHeapContext::ToolLender>();
	auto* viewCreator = toolLender->Lend<DescriptorHeapContext::ViewCreator>(licence);

	ResourceGetKey resourceGetKey;

	for (int i = 0;i < (int)NumBuffer::kDoubleBuffer;++i)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

		//Rtvを作成
		std::tie(std::ignore, rtvCPU, std::ignore) =
			viewCreator->CreateView(colorBuffer->GetResource(resourceGetKey, i), &rtvDesc_);

		//インデックスを書き込む
		colorBuffer->OverrideHeapIndex(proof_,i, rtvCPU);
	}

	Logger::Log("Create: SwapChainResourceRTV", fileName);
}

