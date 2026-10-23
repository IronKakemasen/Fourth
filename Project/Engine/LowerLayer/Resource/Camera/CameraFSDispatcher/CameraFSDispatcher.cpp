#include "PreCompileHeader.h"
#include "CameraFSDispatcher.h"
#include "../CameraContextRuntime/CameraFrontlineSystems.h"


//外部
#include "../../../../EngineInterface.h"

namespace
{
	std::string const fileName = "CameraFSDispatcher.cpp";
}

CameraContext::FrontlineSystemsDispatcher::FrontlineSystemsDispatcher(NexusFieldProof proof_, CameraCreator& cameraCreator_)
{
	//シーンの総数をロード
	auto* miyajison = Miyajison::Get();
	UINT numScene = (UINT)miyajison->LoadData<int>("ProjectConfig", { "numScene" });

	simpleFreeList.Resize(numScene);
	cameraFrontlineSystemsContainer.reserve(numScene);

	UINT i{};
	for (;i < numScene;++i)
	{
		cameraFrontlineSystemsContainer.emplace_back
		(
			std::make_unique<CameraFrontlineSystems>(proof_, cameraCreator_)
		);
	}

	Logger::Log("Instantiate: CameraFrontlineSystems(" + std::to_string(i) + ")", fileName);

}

CameraContext::FrontlineSystemsDispatcher::~FrontlineSystemsDispatcher()
{

}

CameraContext::CameraFrontlineSystems* CameraContext::FrontlineSystemsDispatcher::Dispatch(AgentKey key_)
{
	return cameraFrontlineSystemsContainer[simpleFreeList.Distribute()].get();
}

