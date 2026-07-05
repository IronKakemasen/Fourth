
#include "CommandStructureSwapChain.h"

CommandStructureSwapChain::CommandStructureSwapChain(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandStructureSwapChain::~CommandStructureSwapChain()
{

}


void CommandStructureSwapChain::CreateSwapChain
(
	IDXGIFactory7& dxgiFactory_,
	ID3D12CommandQueue* commandQueue_,
	DXGI_SWAP_CHAIN_DESC1 desc_,
	IDXGISwapChain4** swapChainDoublePtr_,
	const HWND hWnd_
	
)
{
	HRESULT hr = dxgiFactory_.CreateSwapChainForHwnd(commandQueue_, hWnd_, &desc_,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChainDoublePtr_));

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "スワップチェーン生成失敗", "CommandStructureSwapChain.cpp");
	Logger::Log("Create: SwapChain", "CommandStructureSwapChain.cpp");
}
