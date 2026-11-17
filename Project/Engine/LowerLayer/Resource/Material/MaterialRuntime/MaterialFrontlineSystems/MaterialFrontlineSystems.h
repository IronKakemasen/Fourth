#pragma once
#include "../../MaterialContext.h"
#include "../../MaterialAttacher/MaterialAttacher.h"

struct MaterialBatchFormat;

class MaterialContext::FrontlineSystems
{
	//そのシーンの描画対象のMaterialBatchFormatに合わせた情報をかき集める
	class RenderingObjCollector;

public:

	FrontlineSystems
	(
		NexusFieldProof proof_,
		MaterialAttacher& materialAttacher_
	);

	~FrontlineSystems();

	//マテリアルのバッチングに必要な情報を描画対象からかき集める
	void CollectMaterialBatchFormat(Materials* materialsPtr_);

	//マテリアルのバッチングに必要な情報を見せる
	std::vector<MaterialBatchFormat> const& WatchMaterialBatchFormas()const;

	//マテリアルのアタッチ
	template<Material::Type type>
	void AttachMaterial(Materials* materialsPtr_)
	{
#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			materialsPtr_,
			"materialsPtrがぬる(エンジンのせい)",
			"MaterialFrontlineSystems.h"
		);

#endif // _DEBUG

		materialAttacher.Attach<type>(materialsPtr_);
	}

private:

	MaterialAttacher& materialAttacher;
	std::unique_ptr<RenderingObjCollector> renderingObjCollector;
};

