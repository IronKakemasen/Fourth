#include "PreCompileHeader.h"
#include "GameObjController.h"
#include "ObjDataLoader/ObjDataLoader.h"
#include "../GameObjLibrary/GameObjLibrary.h"
#include "ObjDebugger/ObjDebugger.h"



GameObjectContext::FrontlineSystems::GameObjController::GameObjController(NexusFieldProof proof_)
{

}


void GameObjectContext::FrontlineSystems::GameObjController::Run
(
	ObjLibrary& objLibrary_,
	SceneRuntimeInterface& runtimeInterface_
)
{
	UpdateAllGameObj(objLibrary_, runtimeInterface_);
}

void GameObjectContext::FrontlineSystems::GameObjController::ResetObjTransformFrameFlag(ObjLibrary& objLibrary_)
{
	auto& sortedObjContainer = objLibrary_.RefSortedObjContainer();

	//デバッグUI表示用
#ifndef NDEBUG

	UINT objCnt{};
	auto const& objNameList = objLibrary_.WatchSortedObjContainerNameList();

#endif // !NDEBUG


	//トランスフォームのフレームフラグ関連をリセットする
	for (auto* obj : sortedObjContainer)
	{

		if (!obj->IsActive())
		{

#ifndef NDEBUG

			objCnt++;

#endif // !NDEBUG

			continue;
		}

#ifndef NDEBUG

		ObjDebugger::ShowActiveList(objNameList[objCnt++]);

#endif // !NDEBUG


		auto* trans = obj->GetSystemPtr<Transform>();
		if (!trans) continue;

		//更新1フレームガードをリセット
		trans->ResetFrameFlag();
		//冒頭の減算でカウンタが2になるのは、今フレームで再計算されたときだけにする
		trans->DecrementNeedOverrideBufferCnt();


	}

}


void GameObjectContext::FrontlineSystems::GameObjController::UpdateAllGameObj
(
	ObjLibrary& objLibrary_,
	SceneRuntimeInterface& runtimeInterface_
)
{
	//全ゲームオブジェクトのAwake()とStart()を呼ぶ
	auto& sortedObjContainer = objLibrary_.RefSortedObjContainer();
	for (auto* obj : sortedObjContainer)
	{
		if (obj->IsActive())continue;

		//ゲームオブジェクトの更新処理
		obj->Update(runtimeInterface_);

		auto* trans = obj->GetSystemPtr<Transform>();
		if (!trans) continue;

		//ゲームオブジェクトのトランスフォームの更新
		trans->Update();
	}
}

void GameObjectContext::FrontlineSystems::GameObjController::InitAllGameObj
(
	std::string const& sceneName_,
	ObjLibrary& objLibrary_,
	SceneInterfacesPtr sceneInterfacesPtr_
)
{
	//シーンが用意した初期化インターフェース
	auto& sceneInitInterface = *std::get<SceneInitInterface*>(sceneInterfacesPtr_);
	auto& sceneRuntimeInterface = *std::get<SceneRuntimeInterface*>(sceneInterfacesPtr_);


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
