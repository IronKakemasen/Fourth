#pragma once
#include "../../GameObjectCreator/GameObjectCreator.h"


class GameObjectContext::FrontlineSystems
{
	class ObjContainer;

public:

	FrontlineSystems
	(
		NexusFieldProof proof_,
		GameObjectCreator& objCreator_
	);

	~FrontlineSystems();

	template<typename ObjType>
	ObjType* CreateObj(std::string const& name_)
	{
		std::unique_ptr<ObjType> objUnique = objCreator.Create<ObjType>(name_, WatchNumCreate());
		auto* objPtr = objUnique.get();

		ImportObj(name_ + "[" + std::to_string(WatchNumCreate()) + "]", std::move(objUnique));

		return objPtr;
	}


private:

	GameObjectCreator& objCreator;
	std::unique_ptr<ObjContainer> objContainer;

	size_t WatchNumCreate()const;
	void ImportObj(std::string const& objNamePlusID_, std::unique_ptr<GameObjectBehavior>&& obj_);

};

