#pragma once
#include "../../ResourceUploader/ResourceUploader.h"

class CommandContext::ExecutionAgent
{
public:
	ExecutionAgent(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_);

	//リソースをアップロードするときに溜まったコマンドリストをキックしてかつ同期し、閉じる
	void KickAndSynchronizeUploadCommand(NexusFieldProof proof_ );

private:

	CommandContext::ResourceUploader* resourceUploader;
};

