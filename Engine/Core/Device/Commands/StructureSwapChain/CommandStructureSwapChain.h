#pragma once
#include "../DeviceContextCommandBehavior.h"



//SwapChain周りを構築するためのコマンド
struct CommandStructureSwapChain : public DeviceContextCommandBehavior
{
	CommandStructureSwapChain(DeviceContext::GenerateKey generateKey_);
	~CommandStructureSwapChain();

	//スワップチェーンを生成する
	HRESULT CreateSwapChain
	(
		IDXGIFactory7& dxgiFactory_,
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	);

};

