#pragma once
#include "../../CommandContext.h"
#include "../../../../Resource/Buffer/BufferContext.h"
#include "../../ResourceUploader/ResourceUploader.h"


class CommandContext::CommandProvider
{
public:

	//ResourceUploadコマンドの利用許可
	struct UsesResourceUploadCmdPermission;

	CommandProvider(InstanceKey kew_, CommandContext::ResourceUploader* resourceUploader_);

	template<typename PermissionType>
	auto ProvideResourceUploadCommand(PermissionType permission_)
	{
		if constexpr (std::is_same_v<PermissionType, UsesResourceUploadCmdPermission>)
		{
			return resourceUploader->ProvideUploadCommand();
		}
	}

private:


	CommandContext::ResourceUploader* resourceUploader;
};

struct CommandContext::CommandProvider::UsesResourceUploadCmdPermission
{
private:

	friend class BufferContext::BufferUploader;
	explicit UsesResourceUploadCmdPermission() = default;
};

