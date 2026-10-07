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
		std::vector<bool> areMaterialsDirty;
		std::vector<Transform> transforms;
	};

public:

	enum class Type
	{
		//ランタイム時にバッチング、トランスフォームやマテリアルのアップデート対象から外れる
		kStatic,
		//ランタイム時にデータが変動する
		kDynamic,

		kCount
	};

	Model
	(
		Type type_,
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
	auto const WatchModelType()const { return type; }
	//たぶんimguiでモデルの情報を表示するときに使うと思う
	auto const& WatchChangeables()const { return changeableParams; }
	//PSO生成、モデル分別のときに利用
	auto const& WatchRenderStates()const { return modelDesc.WatchRenderStates(); }
	//ランタイムでドローコマンドをたたくため、バッチング先インデックスがどこかを知るために使用
	auto const& WatchPerDrawIndices()const { return modelDesc.WatchPerDrawIndices(); }
	//ドローコマンドオンリー
	auto const& WatchMeshletSize()const { return modelDesc.WatchMeshletSize(); }
	//主にバッファにバッチングするため
	auto const& WatchMaterial(size_t index_)const { return changeableParams.materials[index_]; }
	auto const IsMaterialDirty(size_t index_)const { return changeableParams.areMaterialsDirty[index_]; }
	auto const& WatchTransform(size_t index_)const { return changeableParams.transforms[index_]; }


	//上位レイヤーでモデルのパラメーターを弄るときに
	void ChangeBlendMode(RenderStateComponent::BlendMode dst_);
	void ChangeMaterialType(ShaderPathComponent::MaterialType dst_);
	void ChangeRoughness(size_t index_, float dst_);
	void ChangeMetalic(size_t index_, float dst_);
	void ChangeColor(size_t index_ , Vector4<float> const& dst_);
	template<TextureComponent::TextureType textureType>
	void ChangeTexture(size_t index_, SRVHeapIndex dst_);
	Transform& RefTransform(size_t index_);
	std::span<Transform> RefTransforms();

private:

	Type type;
	ChangeableParams changeableParams;
	ModelDescription modelDesc;

};

