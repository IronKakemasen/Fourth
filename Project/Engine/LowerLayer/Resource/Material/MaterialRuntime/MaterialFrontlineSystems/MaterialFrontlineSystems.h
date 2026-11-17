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
	std::vector<MaterialBatchFormat>& RefMaterialBatchFormats();

	//マテリアルのアタッチ
	template<Material::Type type>
	auto& AttachMaterial(Materials& materials_)
	{
		return materialAttacher.Attach<type>(materials_);
	}

private:

	MaterialAttacher& materialAttacher;
	std::unique_ptr<RenderingObjCollector> renderingObjCollector;
};

