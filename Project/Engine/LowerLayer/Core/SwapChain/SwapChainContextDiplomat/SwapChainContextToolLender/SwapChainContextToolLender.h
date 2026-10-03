#pragma once
#include "../../SwapChainContext.h"


class SwapChainContext::ToolLender
{
	template<typename ToolType>
	struct ToolTypeTraits;

	struct UsesSwapChainBufferLicence;

public:

	template<typename ToolType>
	using LicenceType = typename ToolTypeTraits<ToolType>::Licence;

	ToolLender(NexusFieldProof proof_, SwapChainBuffer* swapChainBuffer_);

	template<typename ToolType>
	auto& Lend(typename ToolTypeTraits<ToolType>::Licence licence_)
	{
		return *std::get<ToolType*>(tools);
	}

private:

	std::tuple<SwapChainBuffer*> tools;

};

template<>
struct SwapChainContext::ToolLender::ToolTypeTraits<SwapChainContext::SwapChainBuffer>
{
	using Licence = UsesSwapChainBufferLicence;
};
