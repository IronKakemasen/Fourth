#pragma once
#include "../MaterialContext.h"

//外部
#include "SimpleFreeList/SimpleFreeList.h"


class MaterialContext::FrontlineSystemsDispatcher
{
public:

	FrontlineSystemsDispatcher(NexusFieldProof proof_,MaterialAttacher& materialAttacher_);
	~FrontlineSystemsDispatcher();

	FrontlineSystems* Dispatch(AgentKey key_);

private:

	std::vector<std::unique_ptr<FrontlineSystems>> materialFrontlineSystemsContainer;
	SimpleFreeList simpleFreeList;

};



