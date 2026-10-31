#pragma once
#include "../../GameObjectCreator/GameObjectCreator.h"
#include "../../GameObjSetupper/GameObjSetupper.h"

class GameObjectContext::FrontlineSystems
{
	class ObjLibrary;
	class GameObjController;

public:

	FrontlineSystems
	(
		NexusFieldProof proof_,
		GameObjectCreator& objCreator_,
		GameObjSetupper& gameObjSetupper_
	);

	~FrontlineSystems();

	//ゲームオブジェクトを生成し、コンテナにぶち込む。
	//これはシーンの初期化で触れる
	template<typename ObjType>
	ObjType* CreateObj(std::string const& name_)
	{
		std::unique_ptr<ObjType> objUnique = objCreator.Create<ObjType>();
		auto* objPtr = objUnique.get();

		ImportObj(name_ , std::move(objUnique));

		return objPtr;
	}

	//ゲームオブジェクトにシステムをアタッチする
	//SceneInitInterfaceで使用可能
	template<typename SystemType>
	SystemType& AttachSystem(GameObjectBehavior& obj_)
	{
		return gameObjSetupper.AttachSystem<SystemType>(obj_);
	}



private:

	GameObjSetupper& gameObjSetupper;
	GameObjectCreator& objCreator;
	std::unique_ptr<ObjLibrary> objLibrary;
	std::unique_ptr<GameObjController> gameObjController;

	void ImportObj
	(
		std::string const& objName_,
		std::unique_ptr<GameObjectBehavior>&& obj_
	);

};

