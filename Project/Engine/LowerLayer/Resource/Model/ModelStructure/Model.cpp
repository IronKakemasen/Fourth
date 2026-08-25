#include "PreCompileHeader.h"
#include "Model.h"


Model::Model(const ModelDescription& modelDesc_)
	:modelDesc(modelDesc_)
{
	
}

std::string const& Model::WatchName()const
{
	return modelDesc.modelName;
}