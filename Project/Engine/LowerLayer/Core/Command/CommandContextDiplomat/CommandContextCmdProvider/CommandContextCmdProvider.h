#pragma once
#include "../../CommandContextCmds.h"
#include "../../CommandContext.h"

class CommandContext::CommandProvider
{
	//コマンドのタイプと許可を紐づける
	template<typename CommandType>
	struct LicenceTypeTraits;

	//ResourceUploadコマンドの利用許可
	struct UsesResourceUploadCmdLicence;

public:

	template<typename CommandType>
	using LicenceType = typename LicenceTypeTraits<CommandType>::Type;

	CommandProvider(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_);

	///コマンド提供
	template<typename CommandType>
	CommandType Provide(typename LicenceTypeTraits<CommandType>::Type licence_);

private:

	CommandContext::ResourceUploader* resourceUploader;
};


template<>
struct CommandContext::CommandProvider::LicenceTypeTraits<CommandContextCmds::UploadCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdLicence;
};

template<>
struct CommandContext::CommandProvider::LicenceTypeTraits<CommandContextCmds::PitchBarrierCommand>
{
	using Type = CommandContext::CommandProvider::UsesResourceUploadCmdLicence;
};



template<>
CommandContextCmds::UploadCommand CommandContext::CommandProvider::Provide<CommandContextCmds::UploadCommand>
(typename LicenceTypeTraits<CommandContextCmds::UploadCommand>::Type licence_);

template<>
CommandContextCmds::PitchBarrierCommand CommandContext::CommandProvider::Provide<CommandContextCmds::PitchBarrierCommand>
(typename LicenceTypeTraits<CommandContextCmds::PitchBarrierCommand>::Type licence_);

