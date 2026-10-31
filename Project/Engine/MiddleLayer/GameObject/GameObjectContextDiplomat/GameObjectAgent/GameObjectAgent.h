#pragma once
#include "../../GameObjectContext.h"

class GameObjectContext::ExecutionAgent
{
public:

	struct SceneContextProof;

	ExecutionAgent(NexusFieldProof proof_, ObjFSDispatcher& objFSDispatcher_);

	//シーンにゲームオブジェクトの前線システムを渡す
	FrontlineSystems* DispatchFrontlineSystems(SceneContextProof proof_);

private:

	ObjFSDispatcher& objFSDispatcher;
};

