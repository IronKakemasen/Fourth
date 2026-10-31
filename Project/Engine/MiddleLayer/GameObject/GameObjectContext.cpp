#include "PreCompileHeader.h"
#include "GameObjectContext.h"
#include "GameObjectCreator/GameObjectCreator.h"
#include "GameObjSetupper/GameObjSetupper.h"
#include "ObjFSDispatcher/ObjFSDispatcher.h"
#include "GameObjectContextDiplomat/GameObjectAgent/GameObjectAgent.h"
#include "GameObjectContextDiplomat/GameObjectContextDiplomat.h"	

namespace
{
	std::string const fileName = "GameObjectContext.cpp";
}

GameObjectContext::GameObjectContext(NexusFieldProof proof_)
{
	Logger::Entry("GameObjectContext: Constructor");

	gameObjectCreator = std::make_unique<GameObjectCreator>(proof_);
	Logger::Log("Instantiate: GameObjectCreator", fileName);

	gameObjSetupper = std::make_unique<GameObjSetupper>(proof_);
	Logger::Log("Instantiate: GameObjSetupper", fileName);

	objFSDispatcher = std::make_unique<ObjFSDispatcher>(proof_,*gameObjectCreator,*gameObjSetupper);
	Logger::Log("Instantiate: ObjFSDispatcher", fileName);

	diplomat = std::make_unique<GameObjectContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *objFSDispatcher)
	);
	Logger::Log("Instantiate: GameObjectContextDiplomat", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);


	Logger::End("GameObjectContext: Constructor");

}


GameObjectContext::~GameObjectContext()
{

}
