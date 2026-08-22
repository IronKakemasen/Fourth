#pragma once
#include "../../RootSignatureAssembler.h"


class RootSignatureContext::Assembler::StaticSamplerDescCreator
{
	friend class RootSignatureContext::Assembler;

	static std::vector<D3D12_STATIC_SAMPLER_DESC> Create(const RootSignatureDesc::Graphics& srcDesc_);

	static void SetBranchedDetails(D3D12_STATIC_SAMPLER_DESC* desc_, StaticSampler::SamplerState state_);
	static void SetCommonDetails(D3D12_STATIC_SAMPLER_DESC* desc_);
	static void SetDetailsDirectly
	(
		D3D12_STATIC_SAMPLER_DESC* desc_,
		RootSignatureLayoutComponent::ShaderStage shaderStage_,
		uint32_t registerNum_
	);

};

