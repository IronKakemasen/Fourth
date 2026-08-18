#pragma once
#include "AllPassFwd.h"

namespace RenderPassName
{
	template<typename PassType>
	struct PassTypeToName;

	template<>
	struct PassTypeToName<SceneTextureCreator>
	{
		static inline const std::string name = "SceneTextureCreator";
	};

}