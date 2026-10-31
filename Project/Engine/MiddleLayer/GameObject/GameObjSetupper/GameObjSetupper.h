#pragma once
#include "../GameObjectContext.h"
#include "../GameObjectStructure/GameObjectBehavior.h"

class GameObjectContext::GameObjSetupper
{
public:

	GameObjSetupper(NexusFieldProof proof_);

	//システムを取り付ける
	template<typename SystemType>
	SystemType& AttachSystem(GameObjectBehavior& obj_)
	{
		std::get<std::unique_ptr<SystemType>>(obj_.systems) = std::make_unique<SystemType>();

		return *std::get<std::unique_ptr<SystemType>>(obj_.systems);
	}


private:


};

