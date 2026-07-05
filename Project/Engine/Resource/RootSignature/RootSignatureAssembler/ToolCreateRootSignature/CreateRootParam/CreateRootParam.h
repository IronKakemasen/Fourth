#pragma once
#include "../../RootSignatureDesc.h"

struct CreateRootParam
{
	///全シェーダー間で共通のグローバルコンスタントバッファのルートパラメーター生成関数
	std::vector<D3D12_ROOT_PARAMETER> CreateRootparamGloballyCommonCBV(const RootSignatureDesc::Graphics& srcDesc_);

};

