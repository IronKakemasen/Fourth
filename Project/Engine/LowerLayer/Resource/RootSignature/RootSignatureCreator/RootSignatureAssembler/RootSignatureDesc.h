#pragma once
#include "RootSignatureLayoutComponent.h"
#include "../../../../../../Assets/Shared/StaticSampler.h"

namespace RootSignatureDesc
{
	struct Graphics
	{
		std::vector<std::pair<RootSignatureLayoutComponent::ShaderStage, StaticSampler::SamplerState>>
			pairshaderStage_samplerStateContainer;
	};


}

