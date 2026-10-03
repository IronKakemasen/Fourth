#pragma once

class Nexus;
class CommandContextDiplomat;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;
class WindowContextDiplomat;


class SwapChainContext
{
	//画面の表示、バックバッファの切り替えを担う
	class Presenter;
	//初期セットアップを行う
	class Builder;
	//スワップチェーン産の生リソースをもとに作られるバッファ
	class SwapChainBuffer;

public:

	//Nexusのみ生成可能
	struct NexusFieldProof;

	SwapChainContext
	(
		NexusFieldProof proof_,
		DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_,
		DeviceContextDiplomat& deviceContextDiplomat_,
		WindowContextDiplomat& windowContextDiplomat_
	);

	~SwapChainContext();
	
	std::unique_ptr<Presenter> presenter;

private:

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	std::unique_ptr<SwapChainBuffer> swapChainBuffer;
};

struct SwapChainContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

