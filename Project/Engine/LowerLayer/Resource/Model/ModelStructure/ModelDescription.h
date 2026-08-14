#pragma once
#include "../../../Render/RenderStateComponent.h"
#include "../../../Render/RenderPass/ShaderPathComponent.h"



///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてConfigurableをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後Configurableもセットする
struct ModelDescription
{
	//コンストラクタで設置可能
	struct Configurable
	{
		Configurable() {};

		std::vector<RenderStateComponent::BlendMode> blendModes;
		RenderStateComponent::CullMode cullMode;
		ShaderPathComponent::MeshType meshType;
		ShaderPathComponent::MaterialType materialType;
	};

	//そのモデルクラス固有の
	struct Unique
	{
		Unique() {};
		Unique(uint32_t dispatchedTransformedMatrixID_) :dispatchedTransformedMatrixID(dispatchedTransformedMatrixID_) {};

		//トランスフォームID
		uint32_t dispatchedTransformedMatrixID{};
	};

	//そのモデルクラス共通
	struct Common
	{
		Common() {};
		Common(MeshDataID meshDataID_) :meshDataID(meshDataID_) {};

		MeshDataID meshDataID{};

	};

};