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

template<Materials::UpdateType type>
void MaterialContext::FrontlineSystems::CollectMaterialBatchFormat(Materials* materialsPtr_)
{
	renderingObjCollector->Collect<type>(materialsPtr_);
}

template<Materials::UpdateType type>
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RefMaterialBatchFormats()
{
	return renderingObjCollector->RefData<type>();
}


template
void MaterialContext::FrontlineSystems::CollectMaterialBatchFormat<Materials::UpdateType::kStatic>(Materials* materialsPtr_);
template
void MaterialContext::FrontlineSystems::CollectMaterialBatchFormat<Materials::UpdateType::kDynamic>(Materials* materialsPtr_);

template
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RefMaterialBatchFormats<Materials::UpdateType::kStatic>();
template
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RefMaterialBatchFormats<Materials::UpdateType::kDynamic>();
