#include "PreCompileHeader.h"
#include "CommandContextCmdProvider.h"
#include "CommandContextCmdProviderLicences.h"
#include "../../ResourceUploader/ResourceUploader.h"

CommandContext::CommandProvider::CommandProvider(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_)
	:resourceUploader(resourceUploader_)
{

}

template<>
CommandContextCmds::UploadCommand CommandContext::CommandProvider::Provide<CommandContextCmds::UploadCommand>
(typename LicenceTypeTraits<CommandContextCmds::UploadCommand>::Type type_)
{
	return resourceUploader->ProvideUploadCommand(ProviderKey{});
}

template<>
CommandContextCmds::PitchBarrierCommand CommandContext::CommandProvider::Provide<CommandContextCmds::PitchBarrierCommand>
(typename LicenceTypeTraits<CommandContextCmds::PitchBarrierCommand>::Type type_)
{
	return resourceUploader->ProvideBarrierPitchCommand(ProviderKey{});
}



