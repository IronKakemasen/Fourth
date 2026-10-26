#pragma once
#include "../CameraContext.h"
#include "SimpleFreeList/SimpleFreeList.h"

class CameraContext::FrontlineSystemsDispatcher
{
public:

	FrontlineSystemsDispatcher(NexusFieldProof proof_ ,CameraCreator& cameraCreator_);
	~FrontlineSystemsDispatcher();

	FrontlineSystems* Dispatch(AgentKey key_);

private:

	std::vector<std::unique_ptr<FrontlineSystems>> cameraFrontlineSystemsContainer;
	SimpleFreeList simpleFreeList;
};

