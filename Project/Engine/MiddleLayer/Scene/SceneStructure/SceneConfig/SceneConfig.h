#pragma once
#include "../SceneBehavior.h"

struct SceneBehavior::SceneConfig
{

	SceneConfig
	(
		bool alwaysUpdateStatic_
	):alwaysUpdateStatic(alwaysUpdateStatic_){}


	//staticなものを常に更新するかどうかのフラグ
	bool alwaysUpdateStatic = true;

};