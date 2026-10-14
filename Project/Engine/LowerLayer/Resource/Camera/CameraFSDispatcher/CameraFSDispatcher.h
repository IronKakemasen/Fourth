#pragma once
#include "../CameraContext.h"
#include "SimpleFreeList/SimpleFreeList.h"

class CameraContext::FrontlineSystemsDispatcher
{
public:

	FrontlineSystemsDispatcher(NexusFieldProof proof_ ,CameraCreator& cameraCreator_);
	~FrontlineSystemsDispatcher();

	CameraFrontlineSystems& Dispatch(AgentKey key_);

private:

	std::vector<std::unique_ptr<CameraFrontlineSystems>> cameraFrontlineSystemsContainer;
	SimpleFreeList simpleFreeList;
};

