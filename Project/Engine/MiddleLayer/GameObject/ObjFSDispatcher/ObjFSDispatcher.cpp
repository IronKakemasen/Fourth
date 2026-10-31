#include "PreCompileHeader.h"
#include "ObjFSDispatcher.h"
#include "../GameObjectRuntime/GameObjFrontSystems/GameObjFrontlineSystems.h"


GameObjectContext::ObjFSDispatcher::ObjFSDispatcher
(
	NexusFieldProof proof_,
	GameObjectCreator& gameObjectCreator_,
	GameObjSetupper& gameObjSetupper_
)
{
	//シーンの総数をロード
	auto* miyajison = Miyajison::Get();
	UINT numScene = (UINT)miyajison->LoadData<int>("ProjectConfig", { "numScene" });

	simpleFreeList.Resize(numScene, "ModelSys");
	frontlineSystems.reserve(numScene);

	UINT i{};
	for (;i < numScene;++i)
	{
		frontlineSystems.emplace_back(std::make_unique<FrontlineSystems>(proof_, gameObjectCreator_, gameObjSetupper_));
	}

	Logger::Log("Instantiate: FrontlineSystems(" + std::to_string(i) + ")", "ObjFSDispatcher.cpp");

}

GameObjectContext::ObjFSDispatcher::~ObjFSDispatcher()
{

}


GameObjectContext::FrontlineSystems* GameObjectContext::ObjFSDispatcher::Dispatch(AgentKey key_)
{
	return frontlineSystems[simpleFreeList.Distribute()].get();
}

