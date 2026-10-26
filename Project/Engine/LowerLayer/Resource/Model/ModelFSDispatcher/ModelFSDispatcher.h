#pragma once
#include "../ModelContext.h"


//外部
#include "SimpleFreeList/SimpleFreeList.h"


class ModelContext::ModelFSDispatcher
{
public:

	ModelFSDispatcher(NexusFieldProof proof_, ModelCreator& modelCreator_);
	~ModelFSDispatcher();


	FrontlineSystems* Dispatch(AgentKey key_);


private:

	std::vector<std::unique_ptr<FrontlineSystems>> frontlineSystems;
	SimpleFreeList simpleFreeList;
};

