#pragma once
#include "../CommandContext.h"

class CommandContext::ResourceUploader
{

public:

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
	UploadCommand ProvideUploadCommand();

private:

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	ID3D12CommandQueue* commandQueue;
	Synchronizer* synchronizer;

	//リソースのアップロードのコマンドの記録開始
	void RecordingStart();

};
