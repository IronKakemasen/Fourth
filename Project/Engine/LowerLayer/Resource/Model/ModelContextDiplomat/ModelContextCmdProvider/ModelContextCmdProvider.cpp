#include "PreCompileHeader.h"
#include "ModelContextCmdProvider.h"
#include "../../ModelContainer/ModelContainer.h"
#include "../../CreateModelTools/ModelCreator.h"
#include "ModelContextCmdProviderLicences.h"

using namespace ModelContextCmds;

ModelContext::CommandProvider::CommandProvider
(
	NexusFieldProof proof_,
	ModelContainer& modelContainer_,
	ModelCreator& modelCreator_
) :modelContainer(modelContainer_), modelCreator(modelCreator_)
{

}


template<>
WatchModelContainer ModelContext::CommandProvider::Provide<WatchModelContainer>
(typename CmdTypeTraits<WatchModelContainer>::Type licence_)
{
	return modelContainer.WatchModelDataCmd(ProviderKey{});
}

template<>
WatchSeparatedByRenderState ModelContext::CommandProvider::Provide<WatchSeparatedByRenderState>
(typename CmdTypeTraits<WatchSeparatedByRenderState>::Type licence_)
{
	return modelContainer.WatchSeparatedByRenderStateCmd(ProviderKey{});
}

template<>
ModelContextCmds::WatchAllModelsRenderStatePattern ModelContext::CommandProvider::Provide<ModelContextCmds::WatchAllModelsRenderStatePattern>
(typename CmdTypeTraits<ModelContextCmds::WatchModelContainer>::Type licence_)
{
	return modelCreator.WatchAllRenderStatesCmd(ProviderKey{});
}


