#pragma once
#include "../../GameObjectContext.h"

class GameObjectContext::FrontlineSystems
{
	class ObjContainer;

public:

	FrontlineSystems(NexusFieldProof proof_,GameObjectCreator& objCreator_);
	~FrontlineSystems();


private:
	GameObjectCreator& objCreator;
	std::unique_ptr<ObjContainer> objContainer;
};

