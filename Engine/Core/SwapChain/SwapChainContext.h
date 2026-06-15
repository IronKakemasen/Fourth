#pragma once

class WinApp;
class ViewCreator;


class SwapChainContext
{
	//swapChain生成コマンド
	using CommandCreateSwapChain = std::function< HRESULT
	(
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	)>;

public:

	//WinAppのみ生成可能
	struct InstanceKey;
	//バッファの生リソースアドレスを取得キー
	struct ResourceGetKey;

	SwapChainContext
	(
		InstanceKey instanceKey_, 
		ViewCreator& viewCreator_,
		CommandCreateSwapChain cmdCreateSwapChain_,
		float clearColor_[4],
		DXGI_FORMAT format_,
		const HWND hWnd_,
		ID3D12CommandQueue* commandQueue_
	);

	~SwapChainContext();
	
private:

	void Assemble
	(
		InstanceKey instanceKey_,
		ViewCreator& viewCreator_,
		CommandCreateSwapChain cmdCreateSwapChain_,
		float clearColor_[4],
		DXGI_FORMAT format_,
		const HWND hWnd_,
		ID3D12CommandQueue* commandQueue_
	);

	void CreateSwapChain
	(
		CommandCreateSwapChain cmdCreateSwapChain_, 
		const DXGI_SWAP_CHAIN_DESC1& desc_, 
		const HWND hWnd_, 
		ID3D12CommandQueue* commandQueue_
	);

	//スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;

	//スワップチェーン専用のカラーバッファ
	class ColorBuffer;
	std::unique_ptr<ColorBuffer> colorBuffer;

};

struct SwapChainContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};

struct SwapChainContext::ResourceGetKey
{
private:

	friend class SwapChainContext;
	explicit ResourceGetKey() = default;
};
