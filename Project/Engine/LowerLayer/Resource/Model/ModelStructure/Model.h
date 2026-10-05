#pragma once
#include "ModelDescription/ModelDescription.h"
#include "../../../../MiddleLayer/Transform/Transform.h"
#include "../../../Buffer/BufferDefinition/TextureComponent.h"

class Model
{
	//動的に変更可能なパラメーター群
	//RenderPassクラスで、コンポーネントの一致確認でも利用する
	struct ChangeableParams
	{
		bool isVisible = true;
		//現在選択しているブレンドモード
		RenderStateComponent::BlendMode blendMode{};
		//現在選択しているマテリアルタイプ
		ShaderPathComponent::MaterialType materialType{};
		//マテリアル。可変長になっているのは、サブメッシュ分用意しているから
		std::vector<StructuredBufferModelData::MaterialGPU> materials;
		std::vector<Transform> transforms;
	};

public:

	Model
	(
		const ModelDescription& modelDesc_,
		std::vector<StructuredBufferModelData::MaterialGPU> const& materials_
	);

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator=(Model&&) = delete;


	//そのパスで描画するかどうかで利用
	bool DoesDraw
	(
		RenderStateComponent::BlendMode blendMode_,
		ShaderPathComponent::MaterialType materialType_
	)const
	{
		return
		changeableParams.isVisible &&
		changeableParams.blendMode == blendMode_ &&
		changeableParams.materialType == materialType_;
	}

	auto const& WatchName()const { return modelDesc.WatchRenderStates()[0].modelName; }
	//たぶんimguiでモデルの情報を表示するときに使うと思う
	auto const& WatchChangeables()const { return changeableParams; }
	//PSO生成、モデル分別のときに利用
	auto const& WatchRenderStates()const { return modelDesc.WatchRenderStates(); }
	//ランタイムでドローコマンドをたたくために使用
	inline auto const& WatchPerDrawIndices()const { return modelDesc.WatchPerDrawIndices(); }
	inline auto const& WatchMeshletSize()const { return modelDesc.WatchMeshletSize(); }

	//上位レイヤーでモデルのパラメーターを弄るときに
	void ChangeBlendMode(RenderStateComponent::BlendMode dst_);
	void ChangeMaterialType(ShaderPathComponent::MaterialType dst_);
	void ChangeRoughness(int index_, float dst_);
	void ChangeMetalic(int index_, float dst_);
	void ChangeColor(int index_ , Vector4<float> const& dst_);
	template<TextureComponent::TextureType textureType>
	void ChangeTexture(int index_, SRVHeapIndex dst_);
	Transform& RefTransform(int index_);
	std::span<Transform> RefTransforms();

private:

	ChangeableParams changeableParams;
	ModelDescription modelDesc;

};

