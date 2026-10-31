#pragma once
#include "../GameObjController.h"

class GameObjectContext::FrontlineSystems::FrontlineSystems::GameObjController::ObjDataLoader
{
	friend class GameObjController;

	static std::vector<std::string> LoadUpdatePriority(std::string const& sceneName_);


	struct DataKey
	{
		static inline std::string const kGameObjectUpdatePriority = "GameObjectUpdatePriority";
	};

};

