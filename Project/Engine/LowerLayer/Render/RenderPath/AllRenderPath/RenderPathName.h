#pragma once
#include "AllPathFwd.h"

namespace RenderPathName
{

	template<typename PathType>
	struct PathTypeToName;

	template<>
	struct PathTypeToName<CreateSceneTexture>
	{
		static inline const std::string name = "CreateSceneTexture";
	};

}