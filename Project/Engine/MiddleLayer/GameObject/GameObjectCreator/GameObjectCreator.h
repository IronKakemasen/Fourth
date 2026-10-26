#pragma once
#include "../GameObjectContext.h"
#include "../GameObjectStructure/GameObjectBehavior.h"

class GameObjectContext::GameObjectCreator
{

public:

	GameObjectCreator(NexusFieldProof proof_);

	template<typename ObjType>
	std::unique_ptr<ObjType> Create
	(
		std::string const& name_,
		UINT id_
	)		
	{
		std::unique_ptr<ObjType> obj = std::make_unique<ObjType>(GameObjectBehavior::Local_CreateLicence{});
		
		//名前とIDをセットする
		static_cast<GameObjectBehavior*>(obj.get())->SetNameAndID(name_, id_);

		return obj;
	}


};

