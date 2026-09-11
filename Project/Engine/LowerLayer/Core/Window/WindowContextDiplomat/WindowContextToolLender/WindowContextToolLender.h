#pragma once
#include "../../WindowContext.h"

class WindowContext::ToolLender
{
	template<typename ToolType>
	struct ToolTypeTraits;

	struct UsesHWNDLicence;
public:

	template<typename ToolType>
	using LicenceType = typename ToolTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_,
		HWND const& HWND_
	);

	template<typename ToolType>
	ToolType& Lend(typename ToolTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType>(tools);
	}


private:

	std::tuple<HWND> tools;
};

template<>
struct WindowContext::ToolLender::ToolTypeTraits<HWND>
{
	using Type = UsesHWNDLicence;
};
