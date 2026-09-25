#pragma once
#include "ModelDescription/ModelDescription.h"

class Model
{
public:

	//動的に変更可能なパラメーター
	//複数設定していないコンポーネントはもちろん不可
	//RenderPassクラスで、コンポーネントの一致を確認する
	struct ChangeableStatus
	{
		bool isVisible = true;
		RenderStateComponent::BlendMode blendMode{};
		ShaderPathComponent::MaterialType materialType{};
	};

	Model(const ModelDescription& modelDesc_);

	std::string const WatchName()const;
	
	//PSO生成、モデル分別用として利用
	auto const& WatchRenderStates()const { return modelDesc.WatchRenderStates(); }
	
	//そのパスで描画するかどうかで利用
	bool DoesDraw
	(
		RenderStateComponent::BlendMode blendMode_,
		ShaderPathComponent::MaterialType materialType_
	)const
	{
		return
		changeableStatus.isVisible &&
		changeableStatus.blendMode == blendMode_ &&
		changeableStatus.materialType == materialType_;
	}

	//ランタイムでドローコマンドをたたくために使用
	inline auto const& WatchPerDrawIndices()const { return modelDesc.WatchPerDrawIndices(); }
	inline auto const& WatchMaterialGPU()const { return modelDesc.WatchMaterialGPU(); }

private:

	
	ChangeableStatus changeableStatus;
	ModelDescription modelDesc;

};

