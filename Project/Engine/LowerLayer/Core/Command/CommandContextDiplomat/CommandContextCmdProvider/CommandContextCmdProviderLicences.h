#pragma once
#include "CommandContextCmdProvider.h"

class BufferContext;

struct CommandContext::CommandProvider::UsesResourceUploadCmdLicence
{
private:

	friend class BufferContext;
	explicit UsesResourceUploadCmdLicence() = default;
};

