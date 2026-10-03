#include "PreCompileHeader.h"
#include "SwapChainContextBuilder.h"
#include "../SwapChainBuffer/SwapChainBuffer.h"



//外部
#include "../../Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../../Command/CommandContextDiplomat/CommandContextToolLender/CommandContextToolLender.h"
#include "../../Command/CommandContextDiplomat/CommandContextToolLender/CmdContextToolLenderLicences.h"


#include "../../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCmdLicences.h"
#include "../../Device/DeviceContextCmds.h"


#include "../../DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"
#include "../../DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"
#include "../../DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLenderLicences.h"
#include "../../DescriptorHeap/ViewCreator/ViewCreator.h"

#include "../../Window/WindowContextDiplomat/WindowContextDiplomat.h"
#include "../../Window/WindowContextDiplomat/WindowContextToolLender/WindowContextToolLender.h"
#include "../../Window/WindowContextDiplomat/WindowContextToolLender/WindowContextToolLenderLicences.h"

namespace 
{
	std::string const fileName = "SwapChainContextBuilder.cpp";
}


using namespace ProjectConfig::Window;
using namespace ProjectConfig::Render;


std::tuple<std::unique_ptr<SwapChainContext::SwapChainBuffer>, Microsoft::WRL::ComPtr<IDXGISwapChain4>> SwapChainContext::Builder::Build
(
	NexusFieldProof proof_,
	DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_,
	CommandContextDiplomat& commandContextDiplomat_,
	DeviceContextDiplomat& deviceContextDiplomat_,
	WindowContextDiplomat& windowContextDiplomat_
)
{
	//スワップチェーン生成
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = CreateSwapChain
	(
		commandContextDiplomat_,
		deviceContextDiplomat_,
		windowContextDiplomat_
	);

	std::unique_ptr<SwapChainContext::SwapChainBuffer> swapChainBuffer = CreateSwapChainBuffers
	(
		proof_,
		*swapChain.Get(),
		descriptorheapContextDiplomat_
	);

	return std::make_tuple(std::move(swapChainBuffer), std::move(swapChain));
}

std::unique_ptr<SwapChainContext::SwapChainBuffer> SwapChainContext::Builder::CreateSwapChainBuffers
(
	NexusFieldProof proof_,
	IDXGISwapChain4& swapChain_,
	DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_
)
{
	std::unique_ptr<SwapChainBuffer> swapChainBuffer;
	//生リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, (UINT)NumBuffer::kDoubleBuffer > resources;

	//スワップチェーンからリソースを引っ張る
	HRESULT hr{};
	for (int i = 0;i < (int)NumBuffer::kDoubleBuffer;++i)
	{
		hr = swapChain_.GetBuffer(i, IID_PPV_ARGS(resources.at(i).GetAddressOf()));
		ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "SwapChainのリソースを引っ張れなかった", fileName);
	}

	//ビュークリエイターを一時的に借りる
	DescriptorHeapContext::ToolLender::LicenceType<DescriptorHeapContext::ViewCreator> licence;
	auto* toolLender = descriptorheapContextDiplomat_.Access<DescriptorHeapContext::ToolLender>();
	auto* viewCreator = toolLender->Lend<DescriptorHeapContext::ViewCreator>(licence);

	//rtvディスク生成
	auto rtvDesc = CreateRTV_Desc();
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, (UINT)NumBuffer::kDoubleBuffer> rtvHandles;

	for (int i = 0;i < (int)NumBuffer::kDoubleBuffer;++i)
	{
		//rtvを作成
		std::tie(std::ignore, rtvHandles[i], std::ignore) = viewCreator->CreateView<>(resources[i].Get(), &rtvDesc);
	}

	Logger::Log("Create SwapChainBuffers", fileName);


	//バッファ生成
	return std::make_unique<SwapChainBuffer>(proof_,std::move(resources), rtvHandles);
}


D3D12_RENDER_TARGET_VIEW_DESC SwapChainContext::Builder::CreateRTV_Desc()
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	//出力結果をSRGBに変換する
	rtvDesc.Format = kSwapChainBufferFormat;
	//2Dテクスチャとして書き込む
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.PlaneSlice = 0;
	rtvDesc.Texture2D.MipSlice = 0;

	return rtvDesc;
}

DXGI_SWAP_CHAIN_DESC1 SwapChainContext::Builder::CreateSwapChainDesc()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//画面の縦横。クライアント領域と同じにしておく
	swapChainDesc.Width = (UINT)kWidth;
	swapChainDesc.Height = (UINT)kHeight;
	//色の形成
	swapChainDesc.Format = kSwapChainBufferFormat;
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

Microsoft::WRL::ComPtr<IDXGISwapChain4> SwapChainContext::Builder::CreateSwapChain
(
	CommandContextDiplomat& commandContextDiplomat_,
	DeviceContextDiplomat& deviceContextDiplomat_,
	WindowContextDiplomat& windowContextDiplomat_
)
{
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;

	//コマンドキューを一時的に借りる
	auto* commandContextToolLender = commandContextDiplomat_.Access<CommandContext::ToolLender>();
	CommandContext::ToolLender::LicenceType<ID3D12CommandQueue> cmdQueueAccesslicence{};
	auto* commandQueue = commandContextToolLender->Lend<ID3D12CommandQueue>(cmdQueueAccesslicence);

	//スワップチェーン生成コマンドを借りる
	auto commandProvider = deviceContextDiplomat_.Access<DeviceContext::CommandProvider>();
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateSwapChain> dLicence;
	auto createSwapChainCmd = commandProvider->Provide<DeviceContextCmds::CreateSwapChain>(dLicence);

	//windowContexのhwndを借りる
	auto toolLender = windowContextDiplomat_.Access<WindowContext::ToolLender>();
	WindowContext::ToolLender::LicenceType<HWND> hwndLicence;
	auto const& hwnd = toolLender.Lend<HWND>(hwndLicence);

	createSwapChainCmd(commandQueue, CreateSwapChainDesc(), swapChain.GetAddressOf(), hwnd);
	Logger::Log("Create SwapChain", fileName);

	return swapChain;
}
