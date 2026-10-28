#pragma once
#include "../GameObjectContext.h"
#include "../GameObjectStructure/GameObjectBehavior.h"

class GameObjectContext::GameObjectCreator
{

public:

	GameObjectCreator(NexusFieldProof proof_);

	template<typename ObjType>
	std::unique_ptr<ObjType> Create()		
	{
		return std::make_unique<ObjType>(GameObjectBehavior::Local_CreateLicence{});
	}


};

