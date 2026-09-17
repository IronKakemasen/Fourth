#pragma once
#include "../TextureContext.h"


class TextureContextDiplomat
{
public:

	TextureContextDiplomat
	(
		TextureContext::NexusFieldProof proof_,
		std::unique_ptr<TextureContext::ToolLender>&& toolLender_
	);

	template<typename ToolType>
	ToolType& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}


private:


	std::tuple
	<
		std::unique_ptr<TextureContext::ToolLender>
	> tools;

};

