#include "PreCompileHeader.h"
#include "GameObjFrontlineSystems.h"
#include "GameObjLibrary/GameObjLibrary.h"
#include "GameObjController/GameObjController.h"

namespace
{
	auto const fileName = "GameObjFrontlineSystems.cpp";
}


GameObjectContext::FrontlineSystems::FrontlineSystems
(
	NexusFieldProof proof_,
	GameObjectCreator& objCreator_,
	GameObjSetupper& gameObjSetupper_
) :objCreator(objCreator_), gameObjSetupper(gameObjSetupper_)
{
	objLibrary = std::make_unique<ObjLibrary>(proof_);
	Logger::Log("Instantiate: ObjLibrary", fileName);

	gameObjController = std::make_unique<GameObjController>(proof_);
	Logger::Log("Instantiate: GameObjController", fileName);

}

GameObjectContext::FrontlineSystems::~FrontlineSystems()
{

}

void GameObjectContext::FrontlineSystems::InitAllGameObj
(
	std::string const& sceneName_,
	SceneInterfacesPtr sceneInterfacesPtr_
)
{
	gameObjController->InitAllGameObj(sceneName_, *objLibrary, sceneInterfacesPtr_);
	Logger::Log(sceneName_ + ": Init All GameObj", fileName);
}


void GameObjectContext::FrontlineSystems::ImportObj
(
	std::string const& objName_,
	std::unique_ptr<GameObjectBehavior>&& obj_
) 
{
	objLibrary->Import(objName_,std::move(obj_));
}

