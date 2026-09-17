#pragma once
#include "../../TextureContext.h"


class TextureContext::ToolLender
{
	template<typename ToolType>
	struct ToolTypeTraits;

	struct UsesTextureLibLicence;

public:

	template<typename ToolType>
	using LicenceType = typename ToolTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_,
		TextureLibrary* textureLibrary_
	);

	template<typename ToolType>
	ToolType& Lend(typename ToolTypeTraits<ToolType>::Type licence_)
	{
		return *std::get<ToolType*>(tools);
	}

private:

	std::tuple
	<
		TextureLibrary*
	>tools;

};


template<>
struct TextureContext::ToolLender::ToolTypeTraits<TextureContext::TextureLibrary>
{
	using Type = UsesTextureLibLicence;
};

