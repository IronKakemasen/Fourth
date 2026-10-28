#pragma once
#include "../../GameObjectCreator/GameObjectCreator.h"


class GameObjectContext::FrontlineSystems
{
	class ObjLibrary;

public:

	FrontlineSystems
	(
		NexusFieldProof proof_,
		GameObjectCreator& objCreator_
	);

	~FrontlineSystems();

	//ゲームオブジェクトを生成し、コンテナにぶち込む。
	template<typename ObjType>
	ObjType* CreateObj(std::string const& name_)
	{
		std::unique_ptr<ObjType> objUnique = objCreator.Create<ObjType>();
		auto* objPtr = objUnique.get();

		ImportObj(name_ , std::move(objUnique));

		return objPtr;
	}

	//コンテナの中のゲームオブジェクトをソートする
	///シーンのInit()が呼ばれた後じゃないとダメ
	void Sort(std::vector<std::string> const& objPriorityList_);


private:

	GameObjectCreator& objCreator;
	std::unique_ptr<ObjLibrary> objLibrary;

	void ImportObj
	(
		std::string const& objName_,
		std::unique_ptr<GameObjectBehavior>&& obj_
	);

};

