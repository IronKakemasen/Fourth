#pragma once

class Nexus;
class CommandContextDiplomat;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;

class SwapChainContext
{
	//swapChain生成コマンド
	using CommandCreateSwapChain = std::function< void
	(
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	)>;

	//画面の表示、バックバッファの切り替えを担う
	class Presenter;

public:

	//Nexusのみ生成可能
	struct NexusFieldProof;
	//バッファの生リソースアドレスを取得キー
	struct ResourceGetKey;
	//専用のカラーバッファ
	class ColorBuffer;
	//描画パスに必要な情報を提供する
	class RenderPassMaterialProvider;

	std::unique_ptr<Presenter> presenter;
	std::unique_ptr<RenderPassMaterialProvider> renderPassMaterialProvider;

	SwapChainContext
	(
		NexusFieldProof proof_,
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
		CommandContextDiplomat* commandContextDiplomat_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		const HWND hWnd_
	);

	~SwapChainContext();
	

private:

	//そのディスクリプション
	struct Description;

	//SwapChainとそのカラーバッファを構築
	void AssembleCoreParts
	(
		NexusFieldProof proof_,
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
		CommandContextDiplomat* commandContextDiplomat_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		const HWND hWnd_
	);

	//スワップチェーンの生成
	void CreateSwapChain
	(
		CommandCreateSwapChain cmdCreateSwapChain_, 
		const DXGI_SWAP_CHAIN_DESC1& desc_, 
		const HWND hWnd_, 
		ID3D12CommandQueue* commandQueue_
	);

	//スワップチェーンからリソースを引っ張ってくる
	void PullResourcesFromSwapChain(std::unique_ptr<Description>&& desc_);
	//RTVの生成
	void CreateRTV
	(
		NexusFieldProof proof_ ,
		const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc_, 
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_
	);

	//スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
	std::unique_ptr<ColorBuffer> colorBuffer;
};

struct SwapChainContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct SwapChainContext::ResourceGetKey
{
private:

	friend class SwapChainContext;
	explicit ResourceGetKey() = default;
};
