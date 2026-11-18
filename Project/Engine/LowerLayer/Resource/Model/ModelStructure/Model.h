#pragma once
#include "ModelDescription/ModelDescription.h"


//外部
#include "../../../../Math/Transform/Transform.h"
#include "../../Material/Materials/Materials.h"

class ModelContext;
class RenderContext;

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
		Material::Type materialType{};

		//マテリアル。可変長になっているのは、サブメッシュ分用意しているから
		std::vector<Materials> materialsContainer;

		//マテリアル。可変長になっているのは、サブメッシュ分用意しているから
		//std::vector<Material::StandardGPU> materials;
		//std::vector<UINT> areMaterialsDirtyCnt;
		
		
		//トランスフォーム。サブメッシュ分用意されている
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
		std::vector<Materials> materialsContainer_
	);

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator=(Model&&) = delete;

	//上位レイヤーでモデルのパラメーターを弄るときに
	void ChangeBlendMode(RenderStateComponent::BlendMode dst_);
	void ChangeMaterialType(Material::Type dst_);
	
	Materials& RefMaterials(size_t index_) 
	{
#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			index_ < changeableParams.materialsContainer.size(),
			modelDesc.WatchRenderStates()[0].modelName + "には" + std::to_string(index_) + "番目のマテリアルはない",
			"Model.h"
		);

#endif
		return changeableParams.materialsContainer[index_]; 
	}

	std::span<Materials> RefMaterialsContainer() { return changeableParams.materialsContainer; }

	Transform& RefTransform(size_t index_)
	{
#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			index_ < changeableParams.transforms.size(),
			modelDesc.WatchRenderStates()[0].modelName + "には" + std::to_string(index_) + "番目のトランスフォームはない",
			"Model.h"
		);

#endif

		return changeableParams.transforms[index_];
	}
	std::span<Transform> RefTransforms() { return changeableParams.transforms; }

private:

	//モデルクラスは上位層でも触るクラスであり、インターフェースを汚したくないので
	friend class ModelContext;
	friend class RenderContext;
	
	//そのパスで描画するかどうかで利用
	bool DoesDraw
	(
		RenderStateComponent::BlendMode blendMode_,
		Material::Type materialType_
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
	Materials const& WatchMaterials(size_t index_)const { return changeableParams.materialsContainer[index_]; }
	auto const& WatchModelConstants()const { return modelDesc.WatchModelConstants(); }
	//ドローコマンドオンリー
	auto const& WatchMeshletSize()const { return modelDesc.WatchMeshletSize(); }
	
	auto const& WatchMaterialsContainer()const { return changeableParams.materialsContainer; }
	auto const& WatchTransform(size_t index_)const { return changeableParams.transforms[index_]; }

	Type type;
	ChangeableParams changeableParams;
	ModelDescription modelDesc;

};

