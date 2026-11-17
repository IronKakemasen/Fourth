#pragma once
#include "../MaterialFrontlineSystems.h"
#include "../../MaterialBatchFormat.h"


class MaterialContext::FrontlineSystems::RenderingObjCollector
{
public:

	RenderingObjCollector(NexusFieldProof proof_);

	void Collect(Materials* materialsPtr_);

	std::vector<MaterialBatchFormat> const& WatchData()const;

private:

	std::vector<MaterialBatchFormat> materialBatchFormats;
};

