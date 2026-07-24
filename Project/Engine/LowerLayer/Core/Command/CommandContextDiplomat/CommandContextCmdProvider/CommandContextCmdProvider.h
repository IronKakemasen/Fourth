#pragma once
#include "../../../../Resource/Buffer/BufferContext.h"
#include "../../ResourceUploader/ResourceUploader.h"


class CommandContext::CommandProvider
{
	//コマンドのタイプと許可を紐づける
	template<typename CommandType>
	struct CommandTypeTraits;

	//ResourceUploadコマンドの利用許可
	struct UsesResourceUploadCmdPermission;

public:

	template<typename CommandType>
	using PermissionType = typename CommandTypeTraits<CommandType>::Type;


	CommandProvider(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_);

	template<typename CommandType>
	auto Provide(typename CommandTypeTraits<CommandType>::Type type_)
	{
		if constexpr (std::is_same_v<CommandType, CommandContext::ResourceUploader::UploadCommand>)
		{
			return resourceUploader->ProvideUploadCommand(CommandContext::ProviderKey{});
		}
		else if constexpr (std::is_same_v<CommandType, CommandContext::ResourceUploader::PitchBarrierCommand>)
		{
			return resourceUploader->ProvideBarrierPitchCommand(CommandContext::ProviderKey{});
		}

	}

private:

	CommandContext::ResourceUploader* resourceUploader;
};


template<>
struct CommandContext::CommandProvider::CommandTypeTraits<CommandContext::ResourceUploader::UploadCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdPermission;
};

template<>
struct CommandContext::CommandProvider::CommandTypeTraits<CommandContext::ResourceUploader::PitchBarrierCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdPermission;
};


struct CommandContext::CommandProvider::UsesResourceUploadCmdPermission
{
private:

	friend class BufferContext::BufferUploader;
	explicit UsesResourceUploadCmdPermission() = default;
};

