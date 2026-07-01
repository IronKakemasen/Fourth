#pragma once
#include "../../RootSignatureLayoutComponent.h"


struct CreateStaticSamplerDesc
{
	D3D12_STATIC_SAMPLER_DESC Create
	(
		RootSignatureLayoutComponent::ShaderStage shaderStage_,
		uint32_t registerNum_,
		RootSignatureLayoutComponent::SamplerState state_
	);

private:

	void SetBranchedDetails(D3D12_STATIC_SAMPLER_DESC* desc_, RootSignatureLayoutComponent::SamplerState state_);
	
	void SetCommonDetails(D3D12_STATIC_SAMPLER_DESC* desc_);

	void SetDetailsDirectly
	(
		D3D12_STATIC_SAMPLER_DESC* desc_,
		RootSignatureLayoutComponent::ShaderStage shaderStage_,
		uint32_t registerNum_
	);


};

