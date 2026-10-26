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
