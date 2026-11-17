#include "PreCompileHeader.h"
#include "MaterialFrontlineSystems.h"
#include "RenderingObjCollector/RenderingObjCollector.h"

namespace
{
	auto const fileName = "MaterialFrontlineSystems.cpp";
}


MaterialContext::FrontlineSystems::FrontlineSystems
(
	NexusFieldProof proof_,
	MaterialAttacher& materialAttacher_
):materialAttacher(materialAttacher_)
{
	renderingObjCollector = std::make_unique<RenderingObjCollector>(proof_);
	Logger::Log("Instantiate: RenderingObjCollector", fileName);


}

MaterialContext::FrontlineSystems::~FrontlineSystems()
{

}



void MaterialContext::FrontlineSystems::CollectMaterialBatchFormat(Materials* materialsPtr_)
{
	renderingObjCollector->Collect(materialsPtr_);
}

std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RefMaterialBatchFormats()
{
	return renderingObjCollector->RefData();
}
