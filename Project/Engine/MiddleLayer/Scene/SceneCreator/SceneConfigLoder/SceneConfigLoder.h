#pragma once
#include "../SceneCreator.h"

class SceneContext::SceneCreator::SceneConfigLoder
{
	friend class SceneCreator;

	static std::unique_ptr<SceneBehavior::SceneConfig> Load(std::string const& sceneName_);


private:

	struct DataKey
	{
		static inline const std::string kAlwaysUpdateStaticB = "alwaysUpdateStatic";
	};


};

