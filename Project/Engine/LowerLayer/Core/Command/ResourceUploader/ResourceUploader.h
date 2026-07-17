#pragma once
#include "../Synchronizer/Synchronizer.h"

class CommandContext::ResourceUploader
{

public:

	//Nexusにコマンドのキックと同期処理＆コマンド閉じをしてもらう
	struct WaitAndKickLicence;

	ResourceUploader
	(
		CommandContext::InstanceKey key_,
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>&& allocator_forUpload_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>&& cmdList_forUpload_,
		ID3D12CommandQueue* commandQueue_,
		Synchronizer* synchronizer_
	);

	//コマンドコンテキスとに呼び出してもらう
	void WaitAndKick(const WaitAndKickLicence& licence_);
	///commandListをラップしたアップロードコマンド
	UploadCommand ProvideUploadCommand(const CommandContext::UsesResourceUploadCmdPermission& permission_);

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



