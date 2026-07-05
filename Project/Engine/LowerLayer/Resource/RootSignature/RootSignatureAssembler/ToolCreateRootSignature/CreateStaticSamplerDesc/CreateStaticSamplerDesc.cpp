
#include "CreateStaticSamplerDesc.h"


using namespace RootSignatureLayoutComponent;

std::vector<D3D12_STATIC_SAMPLER_DESC> CreateStaticSamplerDesc::Create(const RootSignatureDesc::Graphics& srcDesc_)
{
	std::vector<D3D12_STATIC_SAMPLER_DESC> descContainer;
	auto const sizeEntry = srcDesc_.pair_shaderStageSamplerStateContainer.size();

	descContainer.resize(sizeEntry);

	for (int i = 0;i < sizeEntry;++i)
	{
		SetCommonDetails(&descContainer[i]);
		SetBranchedDetails(&descContainer[i], srcDesc_.pair_shaderStageSamplerStateContainer[i].second);
		SetDetailsDirectly(&descContainer[i], srcDesc_.pair_shaderStageSamplerStateContainer[i].first, i);
	}

	return descContainer;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateStaticSamplerDesc::SetBranchedDetails(D3D12_STATIC_SAMPLER_DESC* desc_, SamplerState state_)
{
	switch (state_)
	{
	case SamplerState::kPointWrap:
	{
		desc_->Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	}
	break;

	case SamplerState::kPointClamp:
	{
		desc_->Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	}
	break;

	case SamplerState::kLinearWrap:
	{
		desc_->Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	}
	break;

	case SamplerState::kLinearClamp:
	{
		desc_->Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	}
	break;

	case SamplerState::kAnisotropicWrap:
	{
		desc_->Filter = D3D12_FILTER_ANISOTROPIC;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		desc_->MaxAnisotropy = D3D12_MAX_MAXANISOTROPY;
	}
	break;

	case SamplerState::kAnisotropicClamp:
	{
		desc_->Filter = D3D12_FILTER_ANISOTROPIC;
		desc_->AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		desc_->MaxAnisotropy = D3D12_MAX_MAXANISOTROPY;
	}
	break;
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateStaticSamplerDesc::SetCommonDetails(D3D12_STATIC_SAMPLER_DESC* desc_)
{
	desc_->MipLODBias = D3D12_DEFAULT_MIP_LOD_BIAS;
	desc_->MaxAnisotropy = 1;
	desc_->ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	desc_->BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	desc_->MinLOD = 0.0f;
	desc_->MaxLOD = D3D12_FLOAT32_MAX;
	desc_->RegisterSpace = 0;

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateStaticSamplerDesc::SetDetailsDirectly
(
	D3D12_STATIC_SAMPLER_DESC* desc_,
	RootSignatureLayoutComponent::ShaderStage shaderStage_,
	uint32_t registerNum_
)
{
	desc_->ShaderRegister = registerNum_;
	desc_->ShaderVisibility = D3D12_SHADER_VISIBILITY(RootSignatureLayoutComponent::Convert(shaderStage_));
}
