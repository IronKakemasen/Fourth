#pragma once
#include "../../../Render/RenderPathStructure/RenderStateComponent.h"
#include "../../../Render/RenderPathStructure/ShaderPathComponent.h"



///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてConfigurableをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後Configurableもセットする
struct ModelDescription
{
	//コンストラクタで設置可能
	struct Configurable
	{
		RenderStateComponent::BlendMode blendMode;
		RenderStateComponent::CullMode cullMode;
		ShaderPathComponent::MeshType meshType;
		ShaderPathComponent::MaterialType materialType;
	};

	//そのモデルクラス固有の
	struct Unique
	{
		//トランスフォームID
		uint32_t dispatchedTransformedMatrixID{};
	};

	//そのモデルクラス共通
	struct Common
	{
		MeshDataID meshDataID{};

	};

};