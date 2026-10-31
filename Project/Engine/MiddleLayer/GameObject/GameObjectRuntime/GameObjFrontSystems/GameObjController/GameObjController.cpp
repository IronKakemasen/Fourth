#include "PreCompileHeader.h"
#include "GameObjController.h"
#include "ObjDataLoader/ObjDataLoader.h"
#include "../GameObjLibrary/GameObjLibrary.h"

GameObjectContext::FrontlineSystems::GameObjController::GameObjController(NexusFieldProof proof_)
{

}

void GameObjectContext::FrontlineSystems::GameObjController::InitAllGameObj
(
	std::string const& sceneName_,
	ObjLibrary& objLibrary_,
	SceneInterfacesPtr sceneInterfacesPtr_
)
{
	//シーンファイルからオブジェの初期化に必要な情報を引っ張ってくる
	//オブジェクト更新優先順位リスト
	auto objPriorityList = ObjDataLoader::LoadUpdatePriority(sceneName_);

	//まずはゲームオブジェクトをソートする
	objLibrary_.Sort(objPriorityList);

	//全ゲームオブジェクトのAwake()とStart()を呼ぶ
	auto& sortedObjContainer = objLibrary_.RefObjContainer();
	for (auto* obj : sortedObjContainer)
	{
		
	}

}
