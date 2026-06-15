#include "PreCompileHedder.h"
#include "CommandStructureSwapChain.h"

CommandStructureSwapChain::CommandStructureSwapChain(DeviceContext::CommandProvider::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandStructureSwapChain::~CommandStructureSwapChain()
{

}


HRESULT CommandStructureSwapChain::CreateSwapChain
(
	IDXGIFactory7& dxgiFactory_,
	ID3D12CommandQueue* commandQueue_,
	DXGI_SWAP_CHAIN_DESC1 desc_,
	IDXGISwapChain4** swapChainDoublePtr_,
	const HWND hWnd_
	
)
{
	return dxgiFactory_.CreateSwapChainForHwnd(commandQueue_, hWnd_, &desc_,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChainDoublePtr_));
}
