#include "PreCompileHeader.h"
#include "CameraFSDispatcher.h"
#include "../CameraContextRuntime/CameraFrontlineSystems.h"


namespace
{
	std::string const fileName = "CameraFSDispatcher.cpp";
}

CameraContext::FrontlineSystemsDispatcher::FrontlineSystemsDispatcher(NexusFieldProof proof_, CameraCreator& cameraCreator_)
{
	//シーンの総数をロード
	auto* miyajison = Miyajison::Get();
	UINT numScene = (UINT)miyajison->LoadData<int>("ProjectConfig", { "numScene" });

	simpleFreeList.Resize(numScene,"CameraSys");
	cameraFrontlineSystemsContainer.reserve(numScene);

	UINT i{};
	for (;i < numScene;++i)
	{
		cameraFrontlineSystemsContainer.emplace_back
		(
			std::make_unique<FrontlineSystems>(proof_, cameraCreator_)
		);
	}

	Logger::Log("Instantiate: FrontlineSystems(" + std::to_string(i) + ")", fileName);

}

CameraContext::FrontlineSystemsDispatcher::~FrontlineSystemsDispatcher()
{

}

CameraContext::FrontlineSystems* CameraContext::FrontlineSystemsDispatcher::Dispatch(AgentKey key_)
{
	return cameraFrontlineSystemsContainer[simpleFreeList.Distribute()].get();
}

