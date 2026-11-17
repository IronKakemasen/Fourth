#include "PreCompileHeader.h"
#include "RenderingObjCollector.h"


MaterialContext::FrontlineSystems::RenderingObjCollector::RenderingObjCollector(NexusFieldProof proof_)
{

}

void MaterialContext::FrontlineSystems::RenderingObjCollector::Collect(Materials* materialsPtr_)
{
#ifdef _DEBUG
	ErrorMessageOutput::Assert::DetectError
	(
		materialsPtr_,
		"materialsPtrがぬる(エンジンのせい)",
		"RenderingObjCollector.cpp"
	);
#endif // _DEBUG

	materialBatchFormats.emplace_back(materialsPtr_->materialID, materialsPtr_);
}

std::vector<MaterialBatchFormat>& MaterialContext::FrontlineSystems::RenderingObjCollector::RefData()
{
	return materialBatchFormats;
}