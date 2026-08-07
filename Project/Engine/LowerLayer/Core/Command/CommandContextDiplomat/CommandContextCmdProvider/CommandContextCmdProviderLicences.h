#pragma once
#include "CommandContextCmdProvider.h"
#include "../../../../Resource/Buffer/BufferCreateTools/BufferUploader/BufferUploader.h"

struct CommandContext::CommandProvider::UsesResourceUploadCmdLicence
{
private:

	friend class BufferContext::BufferUploader;
	explicit UsesResourceUploadCmdLicence() = default;
};

