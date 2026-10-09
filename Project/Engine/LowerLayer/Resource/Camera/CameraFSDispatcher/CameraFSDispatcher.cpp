#include "PreCompileHeader.h"
#include "CameraFSDispatcher.h"
#include "../CameraContextRuntime/CameraFrontlineSystems.h"


namespace
{
	std::string const fileName = "CameraFSDispatcher.cpp";
}

CameraContext::FrontlineSystemsDispatcher::FrontlineSystemsDispatcher(NexusFieldProof proof_)
{
	///!!!!!!!!将来的には、シーンのジェーソンファイルの数からシーン数を確定
	//その数分インスタンス化する
	simpleFreeList.Resize(1);

	UINT i = 0;
	for (;i < 1;++i)
	{

		cameraFrontlineSystemsContainer.emplace_back
		(
			std::make_unique<CameraFrontlineSystems>(proof_)
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

