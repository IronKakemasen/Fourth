#pragma once
#include "../CommandContext.h"

class CommandContext::ResourceUploader
{

public:

	//Nexusにコマンドのキックと同期処理＆コマンド閉じをしてもらう
	struct WaitAndKickLicence;

	ResourceUploader
	(
		CommandContext::InstanceKey key_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		ID3D12CommandQueue* commandQueue_,
		CommandContext::Synchronizer* synchronizer_
	);


	//リソースをアップロードするときに溜まったコマンドリストをキックしてかつ同期し、閉じる
	//コアな処理なので鍵付き
	void WaitAndKick(const WaitAndKickLicence& licence_);
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

struct CommandContext::ResourceUploader::WaitAndKickLicence
{
private:

	friend class Nexus;
	explicit WaitAndKickLicence() = default;
};



