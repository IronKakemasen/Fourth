#pragma once
#include "RootSignatureLayoutComponent.h"


namespace RootSignatureDesc
{
	struct Graphics
	{
		std::vector<std::pair<RootSignatureLayoutComponent::ShaderStage, RootSignatureLayoutComponent::SamplerState>>
			pair_shaderStageSamplerStateContainer;
	};


}

