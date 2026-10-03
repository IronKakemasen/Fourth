#pragma once
#include "../SwapChainContext.h"

class SwapChainContext::Builder
{
	friend class SwapChainContext;

	//スワップチェーンを生成し、そのバックバッファとフロントバッファを生成する
	static std::tuple<std::unique_ptr<SwapChainBuffer>, Microsoft::WRL::ComPtr<IDXGISwapChain4>> Build
	(
		NexusFieldProof proof_,
		DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_,
		DeviceContextDiplomat& deviceContextDiplomat_,
		WindowContextDiplomat& windowContextDiplomat_
	);

	//以下ヘルパー
private:
	
	//スワップチェーン生成
	static Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain
	(
		CommandContextDiplomat& commandContextDiplomat_,
		DeviceContextDiplomat& deviceContextDiplomat_,
		WindowContextDiplomat& windowContextDiplomat_
	);
	//フロンとバッファとバックバッファを作成
	static std::unique_ptr<SwapChainBuffer> CreateSwapChainBuffers
	(
		NexusFieldProof proof_,
		IDXGISwapChain4& swapChain_,
		DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_
	);
	//スワップチェーンのバッファのビューディスク作成
	static D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc();
	//スワップチェーンのディスク生成
	static DXGI_SWAP_CHAIN_DESC1 CreateSwapChainDesc();


};

