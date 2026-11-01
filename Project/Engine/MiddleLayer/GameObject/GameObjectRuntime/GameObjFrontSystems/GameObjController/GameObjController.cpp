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
	//シーンが用意した初期化インターフェース
	auto* sceneInitInterface = std::get<SceneInitInterface*>(sceneInterfacesPtr_);
	auto* sceneRuntimeInterface = std::get<SceneRuntimeInterface*>(sceneInterfacesPtr_);


	//シーンのInit()が完了した後なので、この時点でそのシーンの
	//全てのゲームオブジェクト、モデルが作られたことになる
	
	//シーンファイルからオブジェの初期化に必要な情報を引っ張ってくる
	//オブジェクト更新優先順位リスト
	auto objPriorityList = ObjDataLoader::LoadUpdatePriority(sceneName_);

	//まずはゲームオブジェクトをソートする
	objLibrary_.Sort(objPriorityList);

	//全ゲームオブジェクトのAwake()とStart()を呼ぶ
	auto& sortedObjContainer = objLibrary_.RefSortedObjContainer();
	for (auto* obj : sortedObjContainer)
	{
		obj->Awake(sceneInitInterface);
	}

	for (auto* obj : sortedObjContainer)
	{
		obj->Start(sceneRuntimeInterface);
	}

}
