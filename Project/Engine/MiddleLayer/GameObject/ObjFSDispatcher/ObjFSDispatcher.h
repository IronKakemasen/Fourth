#pragma once
#include "../GameObjectContext.h"

//外部
#include "SimpleFreeList/SimpleFreeList.h"




class GameObjectContext::ObjFSDispatcher
{
public:

	ObjFSDispatcher
	(
		NexusFieldProof proof_, 
		GameObjectCreator& gameObjectCreator_,
		GameObjSetupper& gameObjSetupper_
	);

	~ObjFSDispatcher();


	FrontlineSystems* Dispatch(AgentKey key_);


private:

	std::vector<std::unique_ptr<FrontlineSystems>> frontlineSystems;
	SimpleFreeList simpleFreeList;
};

