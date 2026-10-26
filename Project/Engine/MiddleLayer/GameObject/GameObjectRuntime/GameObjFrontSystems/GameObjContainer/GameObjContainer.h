#pragma once
#include "../GameObjFrontlineSystems.h"

class GameObjectBehavior;

class GameObjectContext::FrontlineSystems::ObjContainer
{
public:

	ObjContainer(NexusFieldProof proof_);

	size_t WatchNumObjUnique();

	void Import(std::string const& objNamePlusID_, std::unique_ptr<GameObjectBehavior>&& obj_);


private:

	//本体のマップ
	std::unordered_map<std::string, std::unique_ptr<GameObjectBehavior>> objMap;

};

