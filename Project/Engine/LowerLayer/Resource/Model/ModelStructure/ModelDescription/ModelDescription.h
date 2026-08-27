#pragma once
#include "../../../../Render/RenderStateComponent.h"
#include "../../../../Render/RenderPass/ShaderPathComponent.h"


///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてRenderStatesをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後RenderStatesもセットする
struct ModelDescription
{
	//モデルクラスのコンストラクタで設置可能
	struct RenderState
	{
		RenderState() = default;

		RenderState
		(
			std::vector<RenderStateComponent::BlendMode> blendModes,
			RenderStateComponent::RenderPass passes_,
			RenderStateComponent::CullMode cullMode_,
			ShaderPathComponent::MeshType meshType_,
			ShaderPathComponent::MaterialType materialType_
		): blendModes(std::move(blendModes)),passes(passes),cullMode(cullMode),meshType(meshType),materialType(materialType)
		{}

		//ブレンドモード複数可
		std::vector<RenderStateComponent::BlendMode> blendModes;
		//どの描画パス(ステージ)で描画するか複数可
		RenderStateComponent::RenderPass passes = RenderStateComponent::RenderPass::kNone;
		//どの面をカリングするか
		RenderStateComponent::CullMode cullMode = RenderStateComponent::CullMode::kBack;
		//頂点処理方法
		ShaderPathComponent::MeshType meshType = ShaderPathComponent::MeshType::kStatic;
		//メッシュ描画方法
		ShaderPathComponent::MaterialType materialType = ShaderPathComponent::MaterialType::kStandard;
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
	//中はただの入力チェック
	ModelDescription
	(
		std::vector<ModelDescription::Common> const& modelDescCommons_,
		std::vector<ModelDescription::Unique> const& modelDescUniques_,
		std::string modelName_,
		std::vector<ModelDescription::RenderState> const& modelDescRenderStates_
	);

	inline std::string const WatchName()const { return modelName; }
	inline std::vector<ModelDescription::RenderState> const& WatchRenderStates()const { return renderStates; }

private:

	//ModelDescAssemblerに設定してもらう
	std::vector<ModelDescription::Common> commons;
	std::vector<ModelDescription::Unique> uniques;

	//これ以下は自分で決める
	std::string modelName;
	std::vector<ModelDescription::RenderState> renderStates;

};