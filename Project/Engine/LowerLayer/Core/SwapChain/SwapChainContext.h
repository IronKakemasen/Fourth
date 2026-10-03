#pragma once

class Nexus;
class CommandContextDiplomat;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;
class WindowContextDiplomat;
class SwapChainContextDiplomat;

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
	//代行者限定
	struct AgentKey;
	//ツール貸し出し
	class ToolLender;
	//Nexusフィールドでのアクションを代行する
	class ExecutionAgent;

	SwapChainContext
	(
		NexusFieldProof proof_,
		DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_,
		DeviceContextDiplomat& deviceContextDiplomat_,
		WindowContextDiplomat& windowContextDiplomat_
	);

	~SwapChainContext();
	
	SwapChainContextDiplomat& AccessDiplomat()
	{
		return *diplomat;
	}

private:

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	std::unique_ptr<SwapChainBuffer> swapChainBuffer;
	std::unique_ptr<Presenter> presenter;

	std::unique_ptr<ToolLender> toolLender;
	std::unique_ptr<SwapChainContextDiplomat> diplomat;
};

struct SwapChainContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct SwapChainContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};




