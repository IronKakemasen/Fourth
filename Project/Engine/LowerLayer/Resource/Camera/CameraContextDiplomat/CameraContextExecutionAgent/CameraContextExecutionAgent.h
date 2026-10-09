#pragma once
#include "../../CameraContext.h"

class SceneContext;

class CameraContext::ExecutionAgent
{
	struct SceneContextProof;

public:

	ExecutionAgent
	(
		NexusFieldProof proof_,
		FrontlineSystemsDispatcher& frontlineSystemsDispatcher_
	);


	CameraFrontlineSystems* DispatchFrontlineSystems(SceneContextProof proof_);

private:

	FrontlineSystemsDispatcher& frontlineSystemsDispatcher;

};

struct CameraContext::ExecutionAgent::SceneContextProof
{
private:

	friend class SceneContext;
	explicit SceneContextProof() = default;

};


