#pragma once

class WinApp;
class ViewCreator;


class SwapChainContext
{

public:

	//WinAppのみ生成可能
	struct InstanceKey;
	//バッファの生リソースアドレスを取得キー
	struct ResourceGetKey;

	SwapChainContext
	(
		InstanceKey instanceKey_, 
		ViewCreator& viewCreator_,
		float clearColor_[4],
		DXGI_FORMAT format_
	);

	~SwapChainContext();
	
private:

	void CreateSwapChainColorBuffer
	(
		InstanceKey instanceKey_,
		ViewCreator& viewCreator_,
		float clearColor_[4],
		DXGI_FORMAT format_
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
