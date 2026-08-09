#include "PreCompileHeader.h"
#include "BufferContextCmdProvider.h"
#include "../../GlobalConstantBuffers/GlobalConstantBufferCreator/GlobalConstantBufferCreator.h"
#include "BufferContextCmdProviderLicences.h"

BufferContext::CmdProvider::CmdProvider(NexusFieldProof proof_, GlobalConstantBufferCreator* cBufferCreator_)
	:cBufferCreator(cBufferCreator_)
{

}


template<>
BufferContextCmds::CreateCBufferCmd BufferContext::CmdProvider::Provide
(typename LicenceTypeTraits<BufferContextCmds::CreateCBufferCmd>::Type licence_)
{
	return cBufferCreator->ProvideCreateCBufferCmd(ProviderKey{});
}
