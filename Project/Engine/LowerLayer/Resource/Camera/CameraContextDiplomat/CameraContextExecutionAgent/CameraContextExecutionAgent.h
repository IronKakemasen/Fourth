#pragma once
#include "../../CameraContext.h"

class CameraContext::ExecutionAgent
{

public:

	struct SceneContextProof;

	ExecutionAgent
	(
		NexusFieldProof proof_,
		FrontlineSystemsDispatcher& frontlineSystemsDispatcher_
	);


	CameraFrontlineSystems* DispatchFrontlineSystems(SceneContextProof proof_);

private:

	FrontlineSystemsDispatcher& frontlineSystemsDispatcher;

};

