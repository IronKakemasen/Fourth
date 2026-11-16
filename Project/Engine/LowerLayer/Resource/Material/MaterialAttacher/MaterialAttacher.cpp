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

Materials MaterialContext::MaterialAttacher::CreateMaterials()
{
	return Materials( DispatchMaterialID());
}

UINT MaterialContext::MaterialAttacher::DispatchMaterialID()
{
	return materialIndexDispatcher.DispatchMaterialID();
}


