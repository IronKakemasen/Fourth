#include "PreCompileHeader.h"
#include "MaterialFSDispatcher.h"
#include "../MaterialRuntime/MaterialFrontlineSystems/MaterialFrontlineSystems.h"


namespace
{
	std::string const fileName = "MaterialFSDispatcher.cpp";
}

MaterialContext::FrontlineSystemsDispatcher::FrontlineSystemsDispatcher
(
	NexusFieldProof proof_,
	MaterialAttacher& materialAttacher_
)
{
	//シーンの総数をロード
	auto* miyajison = Miyajison::Get();
	UINT numScene = (UINT)miyajison->LoadData<int>("ProjectConfig", { "numScene" });

	simpleFreeList.Resize(numScene, "MaterialSys");
	materialFrontlineSystemsContainer.reserve(numScene);

	UINT i{};
	for (;i < numScene;++i)
	{
		materialFrontlineSystemsContainer.emplace_back
		(
			std::make_unique<FrontlineSystems>(proof_, materialAttacher_)
		);
	}

	Logger::Log("Instantiate: FrontlineSystems(" + std::to_string(i) + ")", fileName);

}

MaterialContext::FrontlineSystemsDispatcher::~FrontlineSystemsDispatcher()
{

}

MaterialContext::FrontlineSystems* MaterialContext::FrontlineSystemsDispatcher::Dispatch(AgentKey key_)
{
	return materialFrontlineSystemsContainer[simpleFreeList.Distribute()].get();
}
