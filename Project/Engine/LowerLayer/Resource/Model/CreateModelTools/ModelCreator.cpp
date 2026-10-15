#include "PreCompileHeader.h"
#include "ModelCreator.h"
#include "ModelDescAssembler/ModelDescAssembler.h"

namespace
{
	auto const fileName = "ModelCreator.cpp";
}

using namespace StructuredBufferModelData;

ModelContext::ModelCreator::ModelCreator
(
	NexusFieldProof proof_,
	ModelSlotAllocator& slotAllocator_,
	TextureContextDiplomat& textureContextDiplomat_
) 
{
	modelDescAssembler = std::make_unique<ModelDescAssembler>(proof_, slotAllocator_, textureContextDiplomat_);
}


ModelContext::ModelCreator::~ModelCreator()
{

}

std::vector<RenderState>const& ModelContext::ModelCreator::WatchRenderStateCache(AgentKey key_)const
{
	return renderStatesCache;
}

void ModelContext::ModelCreator::DeleteRenderStateCache(NexusFieldProof proof_ , AgentKey key_)
{
	renderStatesCache.clear();
	renderStatesCache.shrink_to_fit();
}


ModelContext::ModelCreator::ModelDescParts ModelContext::ModelCreator::AssembleModelDescParts
(
	std::string const& modelFileName_,
	std::vector<MaterialCPU> const& inputMaterials_
)
{
	return modelDescAssembler->Assemble(modelFileName_, inputMaterials_);
}


