#include "PreCompileHeader.h"
#include "ModelFSDispatcher.h"
#include "../ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"



ModelContext::ModelFSDispatcher::ModelFSDispatcher(NexusFieldProof proof_, ModelCreator& modelCreator_)
{
	//シーンの総数をロード
	auto* miyajison = Miyajison::Get();
	UINT numScene = (UINT)miyajison->LoadData<int>("ProjectConfig", { "numScene" });

	simpleFreeList.Resize(numScene, "ModelSys");
	frontlineSystems.reserve(numScene);

	UINT i{};
	for (;i < numScene;++i)
	{
		frontlineSystems.emplace_back(std::make_unique<FrontlineSystems>(proof_, modelCreator_));
	}

	Logger::Log("Instantiate: FrontlineSystems(" + std::to_string(i) + ")", "ModelFSDispatcher.cpp");

}

ModelContext::ModelFSDispatcher::~ModelFSDispatcher()
{

}


ModelContext::FrontlineSystems* ModelContext::ModelFSDispatcher::Dispatch(AgentKey key_)
{
	return frontlineSystems[simpleFreeList.Distribute()].get();

}
