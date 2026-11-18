#pragma once
#include "../MaterialFrontlineSystems.h"
#include "../../MaterialBatchFormat.h"


class MaterialContext::FrontlineSystems::RenderingObjCollector
{
public:

	RenderingObjCollector(NexusFieldProof proof_);
	
	//数が多いのでヘッダで定義
	template<Materials::UpdateType type>
	void Collect(Materials* materialsPtr_)
	{
#ifdef _DEBUG
		ErrorMessageOutput::Assert::DetectError
		(
			materialsPtr_,
			"materialsPtrがぬる(エンジンのせい)",
			"RenderingObjCollector.cpp"
		);
#endif // _DEBUG

		materialBatchFormatsArr[(UINT)type].emplace_back(materialsPtr_->materialID, materialsPtr_);
	}

	template<Materials::UpdateType type>
	std::vector<MaterialBatchFormat>& RefMaterialBatchFormats();

	std::array<std::vector<MaterialBatchFormat>, (UINT)Materials::UpdateType::kCount>&
		RefMaterialBatchFormatsArr();

private:

	std::array<std::vector<MaterialBatchFormat>, (UINT)Materials::UpdateType::kCount> materialBatchFormatsArr;
};

