#include "PreCompileHeader.h"
#include "BufferContextCmdProvider.h"
#include "../../WorldConstantBuffers/ConstantBufferCreator/ConstantBufferCreator.h"
#include "BufferContextCmdProviderLicences.h"

BufferContext::CmdProvider::CmdProvider(NexusFieldProof proof_, ConstantBufferCreator* cBufferCreator_)
	:cBufferCreator(cBufferCreator_)
{

}


template<>
BufferContextCmds::CreateCBufferCmd BufferContext::CmdProvider::Provide
(typename LicenceTypeTraits<BufferContextCmds::CreateCBufferCmd>::Type licence_)
{
	return cBufferCreator->ProvideCreateCBufferCmd(ProviderKey{});
}
