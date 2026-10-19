#pragma once
#include "../../SceneStructure/SceneBehavior.h"

class RenderingTestScene : public SceneBehavior
{

public:

	//パブリックで
	RenderingTestScene(InstancingLicense license_):SceneBehavior(license_){}

	//ここの中でモデルの生成などの処理を書く。一発しか呼びません。同じくパブリックで
	virtual void Init()override;

};

