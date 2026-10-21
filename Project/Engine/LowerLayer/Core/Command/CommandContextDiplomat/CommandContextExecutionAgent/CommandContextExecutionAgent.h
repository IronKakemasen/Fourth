#pragma once
#include "../../ResourceUploader/ResourceUploader.h"

class CommandContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		NexusFieldProof proof_, 
		CommandContext::ResourceUploader& resourceUploader_,
		RuntimeCommandController& runtimeCommandController_
	);

	//リソースをアップロードするときに溜まったコマンドリストをキックしてかつ同期し、閉じる
	void KickAndSynchronizeUploadCommand(NexusFieldProof proof_ );
	//ランタイムでコマンドの記録を開始する
	void StartRecordingCommands(NexusFieldProof proof_ , UINT frameIndex_);
	//ランタイムでコマンドの転送を行う
	void ExecuteCommands(NexusFieldProof proof_, UINT frameIndex_);

private:

	CommandContext::ResourceUploader& resourceUploader;
	RuntimeCommandController& runtimeCommandController;

};

