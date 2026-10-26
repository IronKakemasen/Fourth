#include "PreCompileHeader.h"
#include "GameObjectBehavior.h"


//外部
#include "../../../LowerLayer/Resource/Model/ModelStructure/Model.h"

GameObjectBehavior::GameObjectBehavior(Local_CreateLicence licence_)
{

}



void GameObjectBehavior::SetNameAndID(std::string const& name_,UINT id_)
{
	name = name_;
	id = id_;
}

void GameObjectBehavior::SetUpdatePriority(UINT updatePriority_)
{
	updatePriority = updatePriority_;
}

