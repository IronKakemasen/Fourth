#pragma once
#include "../../../../Render/RenderStateComponent.h"
#include "../../../../Resource/Shader/ShaderPathComponent/ShaderPathComponent.h"
#include "../../../../Render/RenderPass/RenderPassComponent.h"


//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"


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
		RenderPassComponent::Pass pass = RenderPassComponent::Pass::kSceneOpaque;
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

	ModelDescription() {};
	//中で入力チェック
	ModelDescription
	(
		std::string modelName_,
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
		std::vector<ModelDescription::RenderState> const& renderStates_,
		std::vector<StructuredBufferModelData::MaterialGPU> materials_
	);

	inline std::vector<ModelDescription::RenderState> const& WatchRenderStates()const { return renderStates; }

private:

	//ModelDescAssemblerに設定してもらう
	//可変長になっているのは、マルチメッシュのため！！！！
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> perDrawIndices;

	//これ以下は自分で決める

	//可変長になっているのは、複数分のPassに参加できるようにするため
	//つまり、サブメッシュもすべて同じ設定
	std::vector<ModelDescription::RenderState> renderStates;

	//マテリアル。可変長になっているのは、サブメッシュ分用意しているから
	std::vector<StructuredBufferModelData::MaterialGPU> materials;
};