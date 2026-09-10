#include "PreCompileHeader.h"
#include "CommandContextCmdProvider.h"
#include "CommandContextCmdProviderLicences.h"
#include "../../ResourceUploader/ResourceUploader.h"

CommandContext::CommandProvider::CommandProvider(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_)
	:resourceUploader(resourceUploader_)
{

}

template<>
CommandContextCmds::UploadBufferCommand  CommandContext::CommandProvider::Provide<CommandContextCmds::UploadBufferCommand >
(typename CmdTypeTraits<CommandContextCmds::UploadBufferCommand >::Type licence_)
{
	return resourceUploader->ProvideUploadCommand(ProviderKey{});
}

template<>
CommandContextCmds::PitchBarrierCommand CommandContext::CommandProvider::Provide<CommandContextCmds::PitchBarrierCommand>
(typename CmdTypeTraits<CommandContextCmds::PitchBarrierCommand>::Type licence_)
{
	return resourceUploader->ProvideBarrierPitchCommand(ProviderKey{});
}



