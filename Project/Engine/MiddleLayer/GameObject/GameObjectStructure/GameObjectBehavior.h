#pragma once

//外部
#include "../../../Math/Transform/Transform.h"

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
	
	//システムを取り付ける
	template<typename SystemType>
	void AttachSystem()
	{
		std::get<std::unique_ptr<SystemType>>(systems) = std::make_unique<SystemType>();
	}

	//システムのポインタを取得
	template<typename SystemType>
	auto* GetSystemPtr()
	{
		return 
		std::get<std::unique_ptr<SystemType>>(systems) ?
		std::get<std::unique_ptr<SystemType>>(systems).get() : nullptr;
	}

	Status WatchStatus()const {return status;}

private:

	//ゲームオブジェクトのステータス
	Status status = Status::kActive;
	//名前。検索などに使います
	std::string name = "none";
	//ID
	UINT id = kInvalid;
	//更新処理優先度
	UINT updatePriority{};

	//アタッチ可能なシステム
	std::tuple<std::unique_ptr<Transform>> systems;


	//以下ゲームオブジェクト管理クラスが呼ぶ

	//ただの更新処理
	virtual void Update() = 0;
	//ゲームオブジェクトのリセットに使用。シーンが切り替わった時に呼ばれる
	virtual void Reset() = 0;
	//実質、コンストラクタの代わり
	virtual void Awake() = 0;
	//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
	//検索などはできる
	virtual void Start() = 0;

	//コンストラクタをシンプルにするための、エンジン層で受け持つ初期化関数群
	void SetNameAndID(std::string const& name_, UINT id_);
	void SetUpdatePriority(UINT updatePriority_);

};

struct GameObjectBehavior::Local_CreateLicence
{
private:

	friend class GameObjectContext;
	explicit Local_CreateLicence() = default;
};
