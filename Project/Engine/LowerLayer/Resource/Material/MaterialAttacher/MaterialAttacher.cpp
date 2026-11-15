#include "PreCompileHeader.h"
#include "MaterialAttacher.h"




MaterialContext::MaterialAttacher::MaterialAttacher
(
	NexusFieldProof proof_,
	MaterialIndexDispatcher& materialIndexDispatcher_,
	MaterialDataBatcher& materialDataBatcher_
) :materialIndexDispatcher(materialIndexDispatcher_), materialDataBatcher(materialDataBatcher_)
{

}

std::unique_ptr<Materials> MaterialContext::MaterialAttacher::CreateMaterials()
{
	return std::make_unique<Materials>(Materials::InstantiateLicence{} , DispatchMaterialID());
}

UINT MaterialContext::MaterialAttacher::DispatchMaterialID()
{
	return materialIndexDispatcher.DispatchMaterialID();
}


