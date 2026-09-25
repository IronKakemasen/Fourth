#pragma once
#include "../RenderState.h"

//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"


///2回のフェーズに分けてモデルクラスのデータを埋めていく
///上位層でモデルのファイル名と、サブメッシュ分も含めてRenderStatesをコンストラクタにセット
///モデルファイル名→Commonが定まり、Uniqueを必要数分割り当てる。
///その後RenderStatesを参加するPassの種類分セットする
struct ModelDescription
{
	ModelDescription() {};
	//中で入力チェック
	ModelDescription
	(
		std::string modelName_,
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
		std::vector<RenderState> const& renderStates_,
		std::vector<StructuredBufferModelData::MaterialGPU> materials_
	);

	//初期化フェーズで利用
	inline auto const& WatchRenderStates()const { return renderStates; }
	
	//ランタイムでドローコマンドをたたくために使用
	inline auto const& WatchPerDrawIndices()const { return perDrawIndices; }
	inline auto const& WatchMaterialGPU()const { return materials; }


private:

	//ModelDescAssemblerに設定してもらう
	//可変長になっているのは、マルチメッシュのため！！！！
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> perDrawIndices;

	//これ以下は自分で決める

	//可変長になっているのは、複数分のPassに参加できるようにするため
	//つまり、サブメッシュもすべて同じ設定
	std::vector<RenderState> renderStates;

	//マテリアル。可変長になっているのは、サブメッシュ分用意しているから
	std::vector<StructuredBufferModelData::MaterialGPU> materials;
};