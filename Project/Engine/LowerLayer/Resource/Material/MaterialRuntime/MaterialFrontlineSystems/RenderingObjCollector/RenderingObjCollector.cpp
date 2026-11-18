#include "PreCompileHeader.h"
#include "RenderingObjCollector.h"


MaterialContext::FrontlineSystems::RenderingObjCollector::RenderingObjCollector(NexusFieldProof proof_)
{

}


std::array<std::vector<MaterialBatchFormat>, (UINT)Materials::UpdateType::kCount>&
MaterialContext::FrontlineSystems::RenderingObjCollector::RefMaterialBatchFormatsArr()
{
	return materialBatchFormatsArr;
}


template<Materials::UpdateType type>
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RenderingObjCollector::RefMaterialBatchFormats()
{
	return materialBatchFormatsArr[(UINT)type];
}


template
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RenderingObjCollector::RefMaterialBatchFormats<Materials::UpdateType::kStatic>();
template
std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RenderingObjCollector::RefMaterialBatchFormats<Materials::UpdateType::kDynamic>();
