#pragma once
#include "SceneBehavior.h"

class RenderingTestScene : public SceneBehavior
{

public:

	//パブリックで
	RenderingTestScene(InstancingLicense license_):SceneBehavior(license_){}

	//ここの中でゲームオブジェクトの生成などの処理を書く。一発しか呼びません。
	//アクセス修飾子はどれでも
	virtual void Init()override;

};

