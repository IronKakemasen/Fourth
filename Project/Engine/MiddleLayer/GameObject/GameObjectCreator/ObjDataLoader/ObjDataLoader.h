#pragma once
#include "../../GameObjectContext.h"

class GameObjectContext::ObjDataLoader
{
public:

	std::vector<std::string> LoadUpdatePriority(std::string const& sceneName_);


private:
	struct DataKey
	{
		static inline std::string const kGameObjectUpdatePriority = "GameObjectUpdatePriority";
	};

};

