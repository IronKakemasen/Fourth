#pragma once
#include "../CommandContext.h"

class CommandContext::ResourceUploader
{

public:

	using UploadCommand = std::function<void
	(
		ID3D12Resource* dstResource_,
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)>;

	using PitchBarrierCommand = std::function<void(const std::vector<D3D12_RESOURCE_BARRIER>&)>;

	ResourceUploader
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		ID3D12CommandQueue* commandQueue_,
		CommandContext::Synchronizer* synchronizer_
	);


	//リソースをアップロードするときに溜まったコマンドリストをキックしてかつ同期し、閉じる
	//コアな処理なのでNexusフィールドでしかさせん
	void KickAndSynchronize(const NexusFieldProof& nexusFieldProof_, AgentKey agentKey_);

	///commandListをラップしたアップロードコマンド
	UploadCommand ProvideUploadCommand(ProviderKey providerKey_);
	///commandListをラップした、バリア張りコマンド
	PitchBarrierCommand ProvideBarrierPitchCommand(ProviderKey providerKey_);


private:

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	ID3D12CommandQueue* commandQueue;
	Synchronizer* synchronizer;

	//リソースのアップロードのコマンドの記録開始
	void RecordingStart();

};
