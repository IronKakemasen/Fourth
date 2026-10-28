#include "PreCompileHeader.h"
#include "GameObjFrontlineSystems.h"
#include "GameObjLibrary/GameObjLibrary.h"


namespace
{
	auto const fileName = "GameObjFrontlineSystems.cpp";
}


GameObjectContext::FrontlineSystems::FrontlineSystems(NexusFieldProof proof_, GameObjectCreator& objCreator_)
	:objCreator(objCreator_)
{
	objLibrary = std::make_unique<ObjLibrary>(proof_);
	Logger::Log("Instantiate: ObjLibrary", fileName);

}

GameObjectContext::FrontlineSystems::~FrontlineSystems()
{

}

void GameObjectContext::FrontlineSystems::ImportObj
(
	std::string const& objName_,
	std::unique_ptr<GameObjectBehavior>&& obj_
) 
{
	objLibrary->Import(objName_,std::move(obj_));
}

void GameObjectContext::FrontlineSystems::Sort(std::vector<std::string> const& objPriorityList_)
{
	objLibrary->SortByPriority(objPriorityList_);
}