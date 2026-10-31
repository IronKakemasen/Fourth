#pragma once
#include "GameObjSystems.h"


//外部
#include "../../Scene/SceneStructure/AllSceneInterfaceFwd.h"


class Model;
class GameObjectContext;

class GameObjectBehavior
{
	friend class GameObjectContext;

public:

	enum class Status
	{
		kActive,	//更新します
		kInActive,	//しません
	};

	struct Local_CreateLicence;

	GameObjectBehavior(Local_CreateLicence licence_);
	virtual ~GameObjectBehavior() = default;
	

	//システムのポインタを取得
	template<typename SystemType>
	auto* GetSystemPtr()
	{
		return 
		std::get<std::unique_ptr<SystemType>>(systems) ?
		std::get<std::unique_ptr<SystemType>>(systems).get() : nullptr;
	}

	Status WatchStatus()const { return status; }

private:

	//ゲームオブジェクトのステータス
	Status status = Status::kActive;

	//アタッチ可能なシステム
	GameObjSystems systems;


	//以下ゲームオブジェクト管理クラスが呼ぶ

	//ただの更新処理
	virtual void Update() = 0;
	//ゲームオブジェクトのリセットに使用。シーンが切り替わった時に呼ばれる
	virtual void Reset() = 0;
	//実質、コンストラクタの代わり
	virtual void Awake(SceneInitInterface* sceneInitInterface_) = 0;
	//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
	//検索などはできる
	virtual void Start(SceneRuntimeInterface* sceneRuntimeInterface_) = 0;


};

struct GameObjectBehavior::Local_CreateLicence
{
private:

	friend class GameObjectContext;
	explicit Local_CreateLicence() = default;
};
