#pragma once
#include "../GameObjFrontlineSystems.h"


//外部
#include "../../../../Scene/SceneStructure/AllSceneInterfaceFwd.h"


class GameObjectContext::FrontlineSystems::GameObjController
{
	//ジェーソンファイルからオブジェの情報を引っ張ってくる
	class ObjDataLoader;

public:

	GameObjController(NexusFieldProof proof_);

	//シーンが作成された後に、
	//ゲームオブジェクトの、Awake()とStart()を呼ぶ
	void InitAllGameObj
	(
		std::string const& sceneName_,
		ObjLibrary& objLibrary_,
		SceneInterfacesPtr sceneInterfacesPtr_
	);

private:



};

