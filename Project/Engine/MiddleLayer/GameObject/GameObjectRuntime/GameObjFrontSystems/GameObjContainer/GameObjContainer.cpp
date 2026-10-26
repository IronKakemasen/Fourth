#include "PreCompileHeader.h"
#include "GameObjContainer.h"
#include "../../../GameObjectStructure/GameObjectBehavior.h"

namespace
{
	auto const fileName = "GameObjContainer.cpp";
}

GameObjectContext::FrontlineSystems::ObjContainer::ObjContainer(NexusFieldProof proof_)
{

}



void GameObjectContext::FrontlineSystems::ObjContainer::Import(std::string const& objNamePlusID_, std::unique_ptr<GameObjectBehavior>&& obj_)
{
	objMap[objNamePlusID_] = std::move(obj_);
	Logger::Log("Import: " + objNamePlusID_, fileName);
}

size_t GameObjectContext::FrontlineSystems::ObjContainer::WatchNumObjUnique()
{
	return objMap.size();
}