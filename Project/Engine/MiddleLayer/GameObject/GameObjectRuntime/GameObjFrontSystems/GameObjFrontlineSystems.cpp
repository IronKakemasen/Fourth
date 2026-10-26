#include "PreCompileHeader.h"
#include "GameObjFrontlineSystems.h"
#include "GameObjContainer/GameObjContainer.h"


namespace
{
	auto const fileName = "GameObjFrontlineSystems.cpp";
}


GameObjectContext::FrontlineSystems::FrontlineSystems(NexusFieldProof proof_, GameObjectCreator& objCreator_)
	:objCreator(objCreator_)
{
	objContainer = std::make_unique<ObjContainer>(proof_);
	Logger::Log("Instantiate: ObjContainer", fileName);

}

GameObjectContext::FrontlineSystems::~FrontlineSystems()
{

}

size_t GameObjectContext::FrontlineSystems::WatchNumCreate()const
{
	return objContainer->WatchNumObjUnique();
}

void GameObjectContext::FrontlineSystems::ImportObj(std::string const& objNamePlusID_, std::unique_ptr<GameObjectBehavior>&& obj_)
{
	objContainer->Import(objNamePlusID_, std::move(obj_));
}
