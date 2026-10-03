#include "PreCompileHeader.h"
#include "ModelContextCmdProvider.h"
#include "../../ModelContainer/ModelContainer.h"
#include "ModelContextCmdProviderLicences.h"

using namespace ModelContextCmds;

ModelContext::CommandProvider::CommandProvider(NexusFieldProof proof_, ModelContainer* modelContainer_)
	:modelContainer(modelContainer_)
{

}


template<>
WatchModelContainer ModelContext::CommandProvider::Provide<WatchModelContainer>
(typename CmdTypeTraits<WatchModelContainer>::Type licence_)
{
	return modelContainer->WatchDataCmd(ProviderKey{});
}

template<>
WatchSeparatedModelContainer ModelContext::CommandProvider::Provide<WatchSeparatedModelContainer>
(typename CmdTypeTraits<WatchSeparatedModelContainer>::Type licence_)
{
	return modelContainer->WatchSeparatedCmd(ProviderKey{});
}

