#include "PreCompileHeader.h"
#include "ModelContextCmdProvider.h"
#include "../../ModelContainer/ModelContainer.h"
#include "ModelContextCmdProviderLicences.h"

ModelContext::CommandProvider::CommandProvider(NexusFieldProof proof_, ModelContainer* modelContainer_)
	:modelContainer(modelContainer_)
{

}


template<>
ModelContextCmds::WatchModelContainer ModelContext::CommandProvider::Provide<ModelContextCmds::WatchModelContainer>
(typename LicenceTypeTraits<ModelContextCmds::WatchModelContainer>::Type type_)
{
	return modelContainer->WatchDataCmd(ProviderKey{});
}

