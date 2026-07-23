#pragma once

class Nexus;
class SwapChainContext;
class CommandContextDiplomat;
class DeviceContextDiplomat;

class CommandContext
{
	//ランタイムでのコマンド制御を行う
	class RuntimeCommandController;
	//FenceでCPUとGPUを同期させる
	class Synchronizer;
	//コマンドリストの処理のラッパークラス
	class RuntimeWrapper;

public:

	using UploadCommand = std::function<void
	(
		ID3D12Resource* dstResource_,
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)>;

	//Nexusフィールドの証明
	struct NexusFieldProof;
	//代行者認証キー
	struct AgentKey;



	//リソースのアップロードを行う
	class ResourceUploader;
	//コマンドを提供する
	class CommandProvider;
	//ツールを貸す
	class ToolLender;
	//自クラスの処理を代行する
	class ExecutionAgent;


	CommandContext
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~CommandContext();

	//同期してCloseHandle()する
	void Finalize(NexusFieldProof instanceKey_);

	std::unique_ptr<RuntimeCommandController> runtimeCommandController;
	std::unique_ptr<CommandContextDiplomat> diplomat;


private:

	std::unique_ptr<Synchronizer> synchronizer;
	std::unique_ptr<RuntimeWrapper> runtimeWrapper;
	std::unique_ptr<ResourceUploader> resourceUploader;

	
	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//コマンドアローケータ
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators;
	//コマンドリスト		
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	//カウンタ
	uint64_t commonFenceValue = 0;
	//それぞれのカウンタ
	std::array<uint64_t,(UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> fenceCounters = { 0,0 };
	//フェンスイベント
	HANDLE fenceEvent = nullptr;

	void CreateFenceEvent();
	void InstantiateRuntimeCommandControler();
	void CreateCoreParts(NexusFieldProof instanceKey_,DeviceContextDiplomat* deviceContextDiplomat_);
};


struct CommandContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct CommandContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};


