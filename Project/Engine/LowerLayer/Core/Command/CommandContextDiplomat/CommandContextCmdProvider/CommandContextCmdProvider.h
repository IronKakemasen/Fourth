#pragma once
#include "../../CommandContextCmds.h"
#include "../../CommandContext.h"

class CommandContext::CommandProvider
{
	//コマンドのタイプと許可を紐づける
	template<typename CommandType>
	struct CmdTypeTraits;

	//ResourceUploadコマンドの利用許可
	struct UsesResourceUploadCmdLicence;

public:

	template<typename CommandType>
	using LicenceType = typename CmdTypeTraits<CommandType>::Type;

	CommandProvider(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_);

	///コマンド提供
	template<typename CommandType>
	CommandType Provide(typename CmdTypeTraits<CommandType>::Type licence_);

private:

	CommandContext::ResourceUploader* resourceUploader;
};


template<>
struct CommandContext::CommandProvider::CmdTypeTraits<CommandContextCmds::UploadCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdLicence;
};

template<>
struct CommandContext::CommandProvider::CmdTypeTraits<CommandContextCmds::PitchBarrierCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdLicence;
};



template<>
CommandContextCmds::UploadCommand CommandContext::CommandProvider::Provide<CommandContextCmds::UploadCommand>
(typename CmdTypeTraits<CommandContextCmds::UploadCommand>::Type licence_);

template<>
CommandContextCmds::PitchBarrierCommand CommandContext::CommandProvider::Provide<CommandContextCmds::PitchBarrierCommand>
(typename CmdTypeTraits<CommandContextCmds::PitchBarrierCommand>::Type licence_);

