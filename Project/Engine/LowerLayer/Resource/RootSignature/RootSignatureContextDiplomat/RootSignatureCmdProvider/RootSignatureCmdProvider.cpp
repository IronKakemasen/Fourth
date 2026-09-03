#include "PreCompileHeader.h"
#include "RootSignatureCmdProvider.h"
#include "../../RootSignatureCreator/RootSignatureCreator.h"
#include "RootSigCmdProviderLicences.h"

RootSignatureContext::CmdProvider::CmdProvider(NexusFieldProof proof_, RootSignatureCreator* creator_)
	:creator(creator_)
{

}


template<>
RootSignatureCmds::CreateGraphicsRootSigCmd RootSignatureContext::CmdProvider::Provide<RootSignatureCmds::CreateGraphicsRootSigCmd>
(typename CmdTypeTraits<RootSignatureCmds::CreateGraphicsRootSigCmd>::Type licence_)
{
	return creator->CreateGraphicsrootSigCmd(CmdProviderKey{});
}
