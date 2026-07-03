#pragma once
#include "RootSignatureLayoutComponent.h"


namespace RootSignatureDesc
{
	struct Graphics
	{
		int numConstantBuffers_{};
		std::vector<std::pair<RootSignatureLayoutComponent::ShaderStage, RootSignatureLayoutComponent::SamplerState>>
			pair_shaderStageSamplerStateContainer;
	};


}

