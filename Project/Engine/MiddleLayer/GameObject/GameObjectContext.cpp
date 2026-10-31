#include "PreCompileHeader.h"
#include "GameObjectContext.h"
#include "GameObjectCreator/GameObjectCreator.h"
#include "GameObjSetupper/GameObjSetupper.h"
#include "ObjFSDispatcher/ObjFSDispatcher.h"

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

	


	Logger::End("GameObjectContext: Constructor");

}


GameObjectContext::~GameObjectContext()
{

}
