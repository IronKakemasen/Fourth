#pragma once

//外部
#include "../../../Math/Transform/Transform.h"

class Model;
class GameObjectContext;

class GameObjectBehavior
{
	friend class GameObjectContext;

	enum class Status
	{
		kActive,	//更新します
		kInActive,	//しません
	};

public:

	struct Local_CreateLicence;

	GameObjectBehavior(Local_CreateLicence licence_);
	virtual ~GameObjectBehavior() = default;
	
	auto& RefTransform() { return transform; }
	Status WatchStatus() {return status;}

private:

	Status status = Status::kActive;
	std::string name = "none";
	UINT id = kInvalid;

	Transform transform;
	Model* model = nullptr;



	//以下ゲームオブジェクト管理クラスが触る

	virtual void Update() = 0;
	virtual void Reset() = 0;

	void Init
	(
		std::string const& name_, 
		UINT id_,
		Model* model_
	);

};

struct GameObjectBehavior::Local_CreateLicence
{
private:

	friend class GameObjectContext;
	explicit Local_CreateLicence() = default;
};
