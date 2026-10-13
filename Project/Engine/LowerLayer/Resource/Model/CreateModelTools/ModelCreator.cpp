#include "PreCompileHeader.h"
#include "ModelCreator.h"


namespace
{
	auto const fileName = "ModelCreator.cpp";
}

using namespace StructuredBufferModelData;

ModelContext::ModelCreator::ModelCreator
(
	NexusFieldProof proof_,
	std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
	ModelContext::ModelContainer& modelContainer_
) :modelDescAssembler(std::move(modelAssembler_)), modelContainer(modelContainer_)
{

}

ModelContextCmds::WatchAllModelsRenderStatePattern ModelContext::ModelCreator::WatchAllRenderStatesCmd(ProviderKey key_)const
{
	return [this]()
	{
		return &renderStatesCache;
	};
}

