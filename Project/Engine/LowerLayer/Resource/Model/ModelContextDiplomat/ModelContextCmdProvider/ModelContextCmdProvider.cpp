#include "PreCompileHeader.h"
#include "ModelContextCmdProvider.h"
#include "../../CreateModelTools/ModelCreator.h"
#include "ModelContextCmdProviderLicences.h"

using namespace ModelContextCmds;

ModelContext::CommandProvider::CommandProvider
(
	NexusFieldProof proof_,
	ModelCreator& modelCreator_
) :modelCreator(modelCreator_)
{

}


template<>
ModelContextCmds::WatchAllModelsRenderStatePattern ModelContext::CommandProvider::Provide<ModelContextCmds::WatchAllModelsRenderStatePattern>
(typename CmdTypeTraits<ModelContextCmds::WatchAllModelsRenderStatePattern>::Type licence_)
{
	return modelCreator.WatchAllRenderStatesCmd(ProviderKey{});
}


