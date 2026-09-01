#pragma once
#include "../../../../Render/RenderStateComponent.h"
#include "../../../../Resource/Shader/ShaderPathComponent.h"
#include "../../../../Render/RenderPass/RenderPassComponent.h"


///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてRenderStatesをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後RenderStatesを参加するPassの種類分セットする
struct ModelDescription
{
	//モデルクラスのコンストラクタで設置可能
	struct RenderState
	{
		RenderState() = default;

		//どの描画パス(ステージ)で描画するか
		RenderPassComponent::Pass pass = RenderPassComponent::Pass::kSceneTextureCreatorOpaque;
		//ブレンドモード複数可
		std::vector<RenderStateComponent::BlendMode> blendModes;
		//どの面をカリングするか
		RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
		//頂点処理方法
		ShaderPathComponent::MeshType meshType = ShaderPathComponent::MeshType::kStatic;
		//メッシュ描画方法
		ShaderPathComponent::MaterialType materialType = ShaderPathComponent::MaterialType::kStandard;

		//デバッグ用
		std::string modelName;

	};

	//そのモデルクラス固有の
	struct Unique
	{
		Unique() = default;
		Unique(uint32_t dispatchedTransformedMatrixID_) :dispatchedTransformedMatrixID(dispatchedTransformedMatrixID_) {};

		//トランスフォームID
		uint32_t dispatchedTransformedMatrixID{};
	};

	//そのモデルクラス共通
	struct Common
	{
		Common() = default;
		Common(MeshDataID meshDataID_) :meshDataID(meshDataID_) {};

		MeshDataID meshDataID{};
	};

	ModelDescription() {};
	//中で入力チェック
	ModelDescription
	(
		std::string modelName_,
		std::vector<ModelDescription::Common> const& commons_,
		std::vector<ModelDescription::Unique> const& uniques_,
		std::vector<ModelDescription::RenderState> const& renderStates_
	);

	inline std::vector<ModelDescription::RenderState> const& WatchRenderStates()const { return renderStates; }

private:

	//ModelDescAssemblerに設定してもらう
	//可変長になっているのは、マルチメッシュのため！！！！
	std::vector<ModelDescription::Common> commons;
	std::vector<ModelDescription::Unique> uniques;

	//これ以下は自分で決める
	//可変長になっているのは、複数分のPassに参加できるようにするため。理由がちゃう
	//つまり、サブメッシュもすべて同じ設定
	std::vector<ModelDescription::RenderState> renderStates;

};