#include "PreCompileHeader.h"
#include "ModelFSDispatcher.h"
#include "../ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"



ModelContext::ModelFSDispatcher::ModelFSDispatcher(NexusFieldProof proof_, ModelCreator& modelCreator_)
{
	//ここもシーンの数に依存。本来であれば、ジェーソンファイルからシーンの数が分かるはず
	simpleFreeList.Resize(1);
	frontlineSystems.reserve(1);

	for (size_t i = 0;i < 1;++i)
	{
		frontlineSystems.emplace_back(std::make_unique<ModelFrontlineSystems>(proof_, modelCreator_));
	}

}

ModelContext::ModelFSDispatcher::~ModelFSDispatcher()
{

}


ModelContext::ModelFrontlineSystems* ModelContext::ModelFSDispatcher::Dispatch(AgentKey key_)
{
	return frontlineSystems[simpleFreeList.Distribute()].get();

}
