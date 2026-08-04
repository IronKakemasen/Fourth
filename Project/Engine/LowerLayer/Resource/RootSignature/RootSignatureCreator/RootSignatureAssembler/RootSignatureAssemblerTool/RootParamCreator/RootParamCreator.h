#pragma once
#include "../../RootSignatureAssembler.h"

class RootSignatureContext::Assembler::RootParamCreator
{
	friend class RootSignatureContext::Assembler;

	///全シェーダー間で共通のグローバルコンスタントバッファのルートパラメーター生成関数
	static std::vector<D3D12_ROOT_PARAMETER> CreateRootparamGloballyCommonCBV(const RootSignatureDesc::Graphics& srcDesc_);

};

