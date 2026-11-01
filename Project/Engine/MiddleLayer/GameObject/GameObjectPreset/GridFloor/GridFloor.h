#pragma once
#include "GameObjectBehavior.h"

class GridFloor: public GameObjectBehavior
{
public:

	GridFloor(Local_CreateLicence licence_) :GameObjectBehavior(licence_) {};


private:

	
	//ただの更新処理
	virtual void Update()override;
	//ゲームオブジェクトのリセットに使用。シーンが切り替わった時に呼ばれる
	virtual void Reset()override;
	//実質、コンストラクタの代わり
	virtual void Awake(SceneInitInterface* sceneInitInterface_)override;
	//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
	//検索などはできる
	virtual void Start(SceneRuntimeInterface* sceneRuntimeInterface_)override;


};

