#pragma once
#include "../../../Render/RenderStateComponent.h"
#include "../../../Resource/Shader/ShaderPathComponent/ShaderPathComponent.h"
#include "../../../Render/RenderPass/RenderPassComponent.h"


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
	//メッシュ描画方法も複数可
	std::vector<ShaderPathComponent::MaterialType> materialTypes;

	//デバッグ用
	std::string modelName;

};
