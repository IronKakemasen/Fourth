#pragma once
#include "../../ShaderContext.h"


class ShaderContext::ToolLender
{
	template<typename ToolType>
	struct CmdTypeTraits;


	//ShaderLibraryへのアクセス許可
	struct UsesShaderLibraryLicence;

	std::tuple<ShaderContext::ShaderLibrary*> tools;

public:

	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_, 
		ShaderContext::ShaderLibrary* shaderLibrary_
	);

	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

};


template<>
struct ShaderContext::ToolLender::CmdTypeTraits<ShaderContext::ShaderLibrary>
{
	using Type = UsesShaderLibraryLicence;
};

