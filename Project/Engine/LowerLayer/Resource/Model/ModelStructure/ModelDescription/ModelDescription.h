#pragma once
#include "../../../../Render/RenderStateComponent.h"
#include "../../../../Render/RenderPass/ShaderPathComponent.h"


///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてRenderStatesをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後RenderStatesもセットする
struct ModelDescription
{

	//コンストラクタで設置可能
	struct RenderStates
	{
		RenderStates()  = default;

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
		std::vector<ModelDescription::RenderStates> const& modelDescRenderStates_
	);

	//ModelDescAssemblerに設定してもらう
	std::vector<ModelDescription::Common> modelDescCommons;
	std::vector<ModelDescription::Unique> modelDescUniques;

	//これ以下は自分で決める
	std::string modelName;
	std::vector<ModelDescription::RenderStates> modelDescRenderStates;

};