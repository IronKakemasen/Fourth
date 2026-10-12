#pragma once
#include "AllPathFwd.h"


namespace RenderPathTraits
{
	template<typename PathType>
	struct PathClassTraits;

	template<>
	struct PathClassTraits<CreateSceneTexture>
	{
		static inline std::string const kName = "CreateSceneTexture";
	};



}